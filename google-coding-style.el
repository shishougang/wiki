;; Copyright 2010 Google Inc.
;;
;; Licensed under the Apache License, Version 2.0 (the "License");
;; you may not use this file except in compliance with the License.
;; You may obtain a copy of the License at
;;
;;      http://www.apache.org/licenses/LICENSE-2.0
;;
;; Unless required by applicable law or agreed to in writing, software
;; distributed under the License is distributed on an "AS IS" BASIS,
;; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;; See the License for the specific language governing permissions and
;; limitations under the License.

;; If you want the RETURN key to go to the next line and space over
;; to the right place, add this to your .emacs right after the load-file:
;;
;;    (add-hook 'c-mode-common-hook 'google-make-newline-indent)
;;

;; Javadoc-Style Documentation

(defun google-coding-style/in-doc-brackets-p ()
  "Return whether the point is in a Javadoc-style bracketed expression.
This allows e.g. {@link ClassName} to not be broken across lines
when running \\[fill-paragraph]."
  (save-excursion
    (condition-case err
        (progn
          (backward-up-list)
          (looking-at "{@"))
      (scan-error))))

(defun google-coding-style/set-doc-style ()
  "Configures `fill-paragraph' to respect Javadoc-style tags.
This means that running \\[fill-paragraph] within a comment won't
merge doc tags (e.g. @param) into the previous line and won't
break up bracketed expressions (e.g. {@link ClassName}) among
multiple lines."
  ;; These are unbound in Emacs 21
  (when (and (boundp 'c-setup-paragraph-variables)
             (boundp 'c-paragraph-start))
    (setq c-paragraph-start
          (concat "\\(" (or c-paragraph-start "") "\\|[ \t]*\*[ \t]*@\\)"))
    ;; This is unbound in Xemacs
    (when (boundp 'fill-nobreak-predicate)
      (add-to-list 'fill-nobreak-predicate
                   'google-coding-style/in-doc-brackets-p))
    (let ((c-buffer-is-cc-mode t))
      (c-setup-paragraph-variables))))


;; python-mode

(defadvice python-calculate-indentation (around calculate-with-google-style)
  "Modify Python indentation to match the Google style guide.

Currently, there are two cases in particular that this
handles. Both have to do with multi-line parenthesized
expressions.  In the first case, the default indentation for
such expressions is `python-indent', but Google mandates
`python-continuation-offset' instead. For example:

  function(
      arg_indented_four_spaces)

In the second case, when doubly-nested multi-line parenthesized
expressions exist, Google mandates that the second nested
expression be indented relative to the first, as so:

  function('string' % (
               'format indented relative to first arg'))"
  (unless
      (block nil
        (setq python-indent-list nil
              python-indent-list-length 1)
        ;; These conditions are all taken directly from python.el.
        ;; Not great for code reuse, but probably better than copying
        ;; the entire function.
        (save-excursion
          (beginning-of-line)
          (let* ((syntax (syntax-ppss))
                 (point (point))
                 (open-start (cadr syntax)))
            (when (eq 'string (syntax-ppss-context syntax)) (return))
            (unless (python-continuation-line-p) (return))
            (unless open-start (return))
            (goto-char (1+ open-start))
            (when (with-syntax-table python-space-backslash-table
                    (let ((parse-sexp-ignore-comments t))
                      (condition-case ()
                          (progn (forward-sexp)
                                 (backward-sexp)
                                 (< (point) point))
                        (error nil))))
              (return))
            (goto-char (1+ open-start))
            (setq ad-return-value
                  (if (eolp)
                      (+ (current-indentation) python-continuation-offset)
                    (current-indentation))))))
    ;; If we don't meet the conditions for the Google workarounds,
    ;; use the normal definition.
    ad-do-it))

;; Okay we'll use 2 everywhere for Python
(defun google-set-python-style ()
  (setq py-indent-offset 2)  ; For the third_party python-mode.el

  ;; For GNU Emacs' python.el
  (setq python-indent 2)
  (when (fboundp 'python-calculate-indentation)
    (ad-activate 'python-calculate-indentation)))

(add-hook 'python-mode-hook 'google-set-python-style)


;; perl-mode

;; Let's make perl work properly by default.
;; Never use tabs, and indent by 2 properly.
(defun google-set-perl-style ()
  (interactive)
  (make-local-variable 'perl-indent-level)
  (setq perl-indent-level 2)
  (make-local-variable 'perl-continued-statement-offset)
  (setq perl-continued-statement-offset 2)
  (make-local-variable 'perl-continued-brace-offset)
  (setq perl-continued-brace-offset -2)
  (make-local-variable 'perl-label-offset)
  (setq perl-label-offset -2)
  (setq indent-tabs-mode nil))

(add-hook 'perl-mode-hook 'google-set-perl-style)


;; sh-mode

;; Shell can be consistent too
(defun google-set-sh-style ()
  (interactive)
  (make-local-variable 'sh-basic-offset)
  (setq sh-basic-offset 2)
  (setq indent-tabs-mode nil))

(add-hook 'sh-mode-hook 'google-set-sh-style)


;; c-mode

(setq auto-mode-alist
      (cons '("\\.[ch]$" . c++-mode) auto-mode-alist))

;; For some reason 1) c-backward-syntactic-ws is a macro and 2)  under Emacs 22
;; bytecode cannot call (unexpanded) macros at run time:
(eval-when-compile (require 'cc-defs))

;; Wrapper function needed for Emacs 21 and XEmacs (Emacs 22 offers the more
;; elegant solution of composing a list of lineup functions or quantities with
;; operators such as "add")
(defun google-c-lineup-expression-plus-4 (langelem)
  "Indents to the beginning of the current C expression plus 4 spaces.

This implements title \"Function Declarations and Definitions\" of the Google
C++ Style Guide for the case where the previous line ends with an open
parenthese.

\"Current C expression\", as per the Google Style Guide and as
clarified by subsequent discussions means the whole expression
regardless of the number of nested parentheses, but excluding
non-expression material such as \"if(\" and \"for(\" control
structures.

Suitable for inclusion in `c-offsets-alist'."
  (save-excursion
    (back-to-indentation)
    ;; Go to beginning of *previous* line:
    (c-backward-syntactic-ws)
    (back-to-indentation)
    ;; We are making a reasonable assumption that if there is a control
    ;; structure to indent past, it has to be at the beginning of the line.
    (if (looking-at "\\(\\(if\\|for\\|while\\)\\s *(\\)")
        (goto-char (match-end 1)))
    (vector (+ 4 (current-column)))))

(defconst google-c-style
  `((c-recognize-knr-p . nil)
    (c-enable-xemacs-performance-kludge-p . t)  ; speed up indentation in XEmacs
    (c-basic-offset . 2)
    (indent-tabs-mode . nil)
    (c-comment-only-line-offset . 0)
    (c-hanging-braces-alist . (
                               (defun-open after)
                               (defun-close before after)
                               (class-open after)
                               (class-close before after)
                               (namespace-open after)
                               (inline-open after)
                               (inline-close before after)
                               (block-open after)
                               (block-close . c-snug-do-while)
                               (extern-lang-open after)
                               (extern-lang-close after)
                               (statement-case-open after)
                               (substatement-open after)
                               ))
    (c-hanging-colons-alist . (
                               (case-label)
                               (label after)
                               (access-label after)
                               (member-init-intro before)
                               (inher-intro)
                               ))
    (c-hanging-semi&comma-criteria
     . (c-semi&comma-no-newlines-for-oneline-inliners
        c-semi&comma-inside-parenlist
        c-semi&comma-no-newlines-before-nonblanks))
    (c-indent-comments-syntactically-p . t)
    (comment-column . 40)
    (c-indent-comment-alist . ((other . (space . 2))))
    (c-cleanup-list . (brace-else-brace
                       brace-elseif-brace
                       brace-catch-brace
                       empty-defun-braces
                       defun-close-semi
                       list-close-comma
                       scope-operator))
    (c-offsets-alist . (
                        (arglist-intro google-c-lineup-expression-plus-4)
                        (func-decl-cont . ++)
                        (member-init-intro . ++)
                        (inher-intro . ++)
                        (comment-intro . 0)
                        (arglist-close . c-lineup-arglist)
                        (topmost-intro . 0)
                        (block-open . 0)
                        (inline-open . 0)
                        (substatement-open . 0)
                        (statement-cont
                         .
                         (,(when (fboundp 'c-no-indent-after-java-annotations)
                             'c-no-indent-after-java-annotations)
                          ,(when (fboundp 'c-lineup-assignments)
                             'c-lineup-assignments)
                          ++))
                        (label . /)
                        (case-label . +)
                        (statement-case-open . +)
                        (statement-case-intro . +)  ; case w/o {
                        (access-label . /)
                        (innamespace . 0)
                        ))
    )
  "Google C/C++ Programming Style")

(defun google-set-c-style ()
  (interactive)
  (make-local-variable 'c-tab-always-indent)
  (setq c-tab-always-indent t)
  (google-coding-style/set-doc-style)
  (c-add-style "Google" google-c-style t))

(defun google-make-newline-indent ()
  (interactive)
  (define-key c-mode-base-map "\C-m" 'newline-and-indent)
  (define-key c-mode-base-map [ret] 'newline-and-indent))

(add-hook 'c-mode-common-hook 'google-set-c-style)


;; js2-mode

(defun google-coding-style/indent-anchor-point ()
  "Returns the position of the first nonblank character on the closest previous
nonblank line.

If no such character can be found, returns nil."
  (save-excursion
    (let (return-value)
      (while (and (not return-value)
                  (>= (forward-line -1) 0))
        (when (not (looking-at "^\\s *$"))
            (back-to-indentation)
            (setq return-value (point))))
      return-value)))

(defun google-coding-style/js-indent-lambda-point (parse-status)
  "Returns the position of the beginning of the expression that we should indent
respective to.

If the point is not inside such a lambda construct, returns nil.

PARSE-STATUS is the value of `parse-partial-sexp' at point, passed down from the
caller for efficiency."
  (save-excursion
    (back-to-indentation)
    (let (after-last-paren-open beginning-of-lambda-line)
      (if (and parse-status (nth 1 parse-status)
               (setq after-last-paren-open (1+ (nth 1 parse-status)))
               (goto-char after-last-paren-open)
               (setq beginning-of-lambda-line (point-at-bol))
               (re-search-backward "function\\s *([^);{}]*)\\s *{"
                                   beginning-of-lambda-line t)
               (= (match-end 0) after-last-paren-open)
               (goto-char (match-beginning 0))
               ;; Move back to beginning of expression...
               (progn (js2-mode-forward-sexp -1) t)
               ;; ... and double-check that we are still on the same line:
               (>= (point) beginning-of-lambda-line))
          (point)))))

(defun google-js-proper-indentation (parse-status)
  "Returns the proper indentation for the current line or nil to let the default
function `js-proper-indentation' decide.  Should NOT move point.

PARSE-STATUS is the value of `parse-partial-sexp' at point, passed down from the
caller for efficiency."
  (save-excursion
    (back-to-indentation)
    (let ((indent-anchor (google-coding-style/indent-anchor-point))
          (lambda-point
           (google-coding-style/js-indent-lambda-point parse-status)))
      (cond
       ;; Under anonymous lambdas, indent relative to the containing expression
       ((and indent-anchor lambda-point (>= lambda-point indent-anchor))
        (progn (goto-char lambda-point) (+ js2-basic-offset (current-column))))
       ;; Closing construct of same
       ((and (looking-at "}") lambda-point)
        (progn (goto-char lambda-point) (current-column)))
       ))))

(defadvice js-proper-indentation (around google-coding-style-js-indent)
  "Ask `google-js-proper-indentation' first."
  (unless (setq ad-return-value (google-js-proper-indentation (ad-get-arg 0)))
    ad-do-it))

(defun google-set-js2-style ()
  "Configures js2-mode for compliance with the JavaScript Style Guide"
  (interactive)
  (setq indent-tabs-mode nil)
  (setq js2-basic-offset 2)
  (google-coding-style/set-doc-style)
  (ad-activate 'js-proper-indentation))

(add-hook 'js2-mode-hook 'google-set-js2-style)


;; js-mode

(defun google-set-js-style ()
  "Configures Emacs' built-in js-mode for compliance with the
JavaScript Style Guide."
  (interactive)
  (setq js-indent-level 2)
  (google-coding-style/set-doc-style))

(add-hook 'js-mode-hook 'google-set-js-style)


;; java-mode

(provide 'google-coding-style)
