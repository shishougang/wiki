(setq custom-file "~/.emacs-custom.el")
(load custom-file)

(add-to-list 'load-path "~/git/org-mode/lisp/")
(add-to-list 'load-path "~/git/org-mode/contrib/lisp/")

(show-paren-mode 1)
(menu-bar-mode 0)
(set-face-foreground 'font-lock-keyword-face "DeepSkyBlue1")
(set-face-foreground 'font-lock-string-face "Goldenrod")

(require 'org)
(require 'htmlize)
;; to have things work correctly in batch-mode
(require 'font-lock)
(require 'cc-mode)
(require 'ox-org)
(c-after-font-lock-init)

(setq make-backup-files nil
      vc-handled-backends nil)

(setq org-export-default-language "en"
      org-export-html-extension "html"
      org-export-with-timestamps nil
      org-export-with-section-numbers nil
      org-export-with-tags 'not-in-toc
      org-export-skip-text-before-1st-heading nil
      org-export-with-sub-superscripts '{}
      org-export-with-LaTeX-fragments t
      org-export-with-archived-trees nil
      org-export-highlight-first-table-line t
      org-export-latex-listings-w-names nil
      org-html-head-include-default-style nil
      org-html-head ""
      org-export-htmlize-output-type 'css
      org-startup-folded nil
      org-export-allow-BIND t
      org-publish-list-skipped-files t
      org-publish-use-timestamps-flag t
      org-export-babel-evaluate nil
      org-confirm-babel-evaluate nil)

(eval-after-load "org-html"
'(setq org-html-scripts
       (concat org-html-scripts "\n"
	       "<script type=\"text/javascript\">
    function rpl(expr,a,b) {
      var i=0
      while (i!=-1) {
         i=expr.indexOf(a,i);
         if (i>=0) {
            expr=expr.substring(0,i)+b+expr.substring(i+a.length);
            i+=b.length;
         }
      }
      return expr
    }

    function show_org_source(){
       document.location.href = rpl(document.location.href,\"html\",\"org.html\");
    }
</script>
")))

;; re-export everything regardless of whether or not it's been modified
;; (setq org-publish-use-timestamps-flag nil)

(setq worg-base "~/git/worg/")
(setq worg-htmlroot "/var/www/orgmode.org/worg/")
(setq worg-base-directory worg-base)
(setq worg-base-code-directory (concat worg-base "code/"))
(setq worg-base-color-themes-directory (concat worg-base "color-themes/"))
(setq worg-base-images-directory (concat worg-base "images/"))
(setq worg-publish-directory worg-htmlroot)

(defun set-org-publish-project-alist ()
  "Set publishing projects for Orgweb and Worg."
  (interactive)
  (setq org-publish-project-alist
	`(("worg" :components ("worg-org-faq" "worg-pages" "worg-code" "worg-color-themes" "worg-images" "worg-sources" "worg-extra" "worg-bibtex"))
	  ("orgweb" :components ("orgwebpages" "orgweb-extra"))
	  ("worg-org-faq"
	   :base-directory ,worg-base-directory
	   :base-extension "dummy"
	   :include ("org-faq.org")
	   :html-extension "html"
	   :publishing-directory ,worg-publish-directory
	   :publishing-function (org-html-publish-to-html)
	   :section-numbers nil
	   :table-of-contents nil
	   :html-head "<link rel=\"stylesheet\" title=\"Standard\" href=\"/worg/style/worg.css\" type=\"text/css\" />
<link rel=\"alternate stylesheet\" title=\"Zenburn\" href=\"/worg/style/worg-zenburn.css\" type=\"text/css\" />
<link rel=\"alternate stylesheet\" title=\"Classic\" href=\"/worg/style/worg-classic.css\" type=\"text/css\" />
<link rel=\"SHORTCUT ICON\" href=\"/org-mode-unicorn.ico\" type=\"image/x-icon\" />
<link rel=\"icon\" href=\"/org-mode-unicorn.ico\" type=\"image/ico\" />"
	   :recursive t
	   :html-preamble ,(with-temp-buffer (insert-file-contents "/home/emacs/git/worg/preamble.html") (buffer-string))
	   :html-postamble "<div id=\"show_source\"><input type=\"button\" value=\"Show Org source\" onClick='show_org_source()'></div><div id=\"license\"><p>Documentation from the http://orgmode.org/worg/ website (either in its HTML format or in its Org format) is licensed under the <a href=\"http://www.gnu.org/copyleft/fdl.html\">GNU Free Documentation License version 1.3</a> or later.  The code examples and css stylesheets are licensed under the <a href=\"http://www.gnu.org/licenses/gpl.html\">GNU General Public License v3</a> or later.</p></div>")
	  ("worg-pages"
	   :base-directory ,worg-base-directory
	   :base-extension "org"
	   :exclude "FIXME"
	   :makeindex t
	   :auto-sitemap nil
	   :sitemap-ignore-case t
	   :html-extension "html"
	   :publishing-directory ,worg-publish-directory
	   :publishing-function (org-html-publish-to-html org-org-publish-to-org)
	   :htmlized-source t
	   :section-numbers nil
	   :table-of-contents nil
	   :html-head "<link rel=\"stylesheet\" title=\"Standard\" href=\"/worg/style/worg.css\" type=\"text/css\" />
<link rel=\"alternate stylesheet\" title=\"Zenburn\" href=\"/worg/style/worg-zenburn.css\" type=\"text/css\" />
<link rel=\"alternate stylesheet\" title=\"Classic\" href=\"/worg/style/worg-classic.css\" type=\"text/css\" />
<link rel=\"SHORTCUT ICON\" href=\"/org-mode-unicorn.ico\" type=\"image/x-icon\" />
<link rel=\"icon\" href=\"/org-mode-unicorn.ico\" type=\"image/ico\" />"
	   :recursive t
	   :html-preamble ,(with-temp-buffer (insert-file-contents "/home/emacs/git/worg/preamble.html") (buffer-string))
	   :html-postamble "<div id=\"show_source\"><input type=\"button\" value=\"Show Org source\" onClick='show_org_source()'></div><div id=\"license\"><p>Documentation from the http://orgmode.org/worg/ website (either in its HTML format or in its Org format) is licensed under the <a href=\"http://www.gnu.org/copyleft/fdl.html\">GNU Free Documentation License version 1.3</a> or later.  The code examples and css stylesheets are licensed under the <a href=\"http://www.gnu.org/licenses/gpl.html\">GNU General Public License v3</a> or later.</p></div>")
	  ("worg-code"
	   :base-directory ,worg-base-code-directory
	   :base-extension "html\\|css\\|png\\|js\\|bz2\\|el\\|sty\\|awk\\|pl"
	   :html-extension "html"
	   :publishing-directory "/var/www/orgmode.org/worg/code/"
	   :recursive t
	   :publishing-function org-publish-attachment)
	  ("worg-sources"
	   :base-directory ,worg-base-directory
	   :base-extension "org"
	   :publishing-directory "/var/www/orgmode.org/worg/sources/"
	   :recursive t
	   :publishing-function org-publish-attachment)
	  ("worg-images"
	   :base-directory ,worg-base-directory
	   :base-extension "png\\|jpg\\|gif\\|pdf\\|csv\\|css\\|tex"
	   :publishing-directory ,worg-publish-directory
	   :recursive t
	   :publishing-function org-publish-attachment)
	  ("worg-extra"
	   :base-directory ,worg-base-directory
	   :base-extension "css"
	   :publishing-directory ,worg-publish-directory
	   :publishing-function org-publish-attachment)
	  ("worg-bibtex"
	   :base-directory "/home/emacs/git/worg/org-contrib/bibtex/"
	   :base-extension "bib"
	   :publishing-directory "/var/www/orgmode.org/worg/org-contrib/bibtex/"
	   :recursive nil
	   :publishing-function org-publish-attachment)
	  ("orgwebpages"
	   :base-directory "~/git/orgweb/"
	   :base-extension "org"
	   :html-extension "html"
	   :publishing-directory "/var/www/orgmode.org/"
	   :publishing-function (org-html-publish-to-html)
	   :auto-sitemap nil
	   :section-numbers nil
	   :table-of-contents t
	   :html-head "<link rel=\"SHORTCUT ICON\" href=\"http://orgmode.org/org-mode-unicorn.ico\" type=\"image/x-icon\" />
<link rel=\"icon\" href=\"http://orgmode.org//org-mode-unicorn.ico\" type=\"image/ico\" />
<link rel=\"publisher\" href=\"https://plus.google.com/102778904320752967064\" />"
	   :html-preamble ,(with-temp-buffer (insert-file-contents "/home/emacs/git/orgweb/preamble.html") (buffer-string))
	   :html-postamble nil
	   :exclude "DS_Store"
	   :recursive t)
	  ("orgweb-extra"
	   :base-directory "~/git/orgweb/"
	   :base-extension "css\\|html\\|png\\|jpg\\|js"
	   :publishing-directory "/var/www/orgmode.org/"
	   :publishing-function org-publish-attachment
	   :recursive t))))

(set-org-publish-project-alist)

(defun worg-fix-symbol-table ()
  (when (string-match "org-symbols\\.html" buffer-file-name)
    (goto-char (point-min))
    (while (re-search-forward "<td>&amp;\\([^<;]+;\\)" nil t)
      (replace-match (concat "<td>&" (match-string 1)) t t))))

(defun publish-worg nil
   "Publish Worg."
   (interactive)
   (add-hook 'org-publish-after-export-hook 'worg-fix-symbol-table)
   (let ((org-format-latex-signal-error nil)
	 (worg-base-directory worg-base)
	 (worg-base-code-directory (concat worg-base "code/"))
	 (worg-base-color-themes-directory (concat worg-base "color-themes/"))
	 (worg-base-images-directory (concat worg-base "images/"))
	 (worg-publish-directory worg-htmlroot))
     (set-org-publish-project-alist)
     (message "Emacs %s" emacs-version)
     (org-version)
     (org-publish-project "worg")))

(defun publish-orgweb nil
   "Publish Org web pages."
   (interactive)
   (add-hook 'org-publish-after-export-hook 'worg-fix-symbol-table)
   (let ((org-format-latex-signal-error nil)
	 (org-export-with-sub-superscripts nil))
     (set-org-publish-project-alist)
     (org-publish-project "orgweb")))

(defun parse-org-quotes ()
  "Create ~/orgmode.org/org-quotes.js from org-quotes.org."
  (interactive)
  (load (concat worg-base "code/elisp/worg-fortune.el"))
  (worg-write-fortune-file
   (concat worg-base "org-quotes.org")
   "~/orgmode.org/org-quotes.js"
   120
   "r_text[%d] = \"%s\";" "\n"
   'worg-fortune-insert-javascript-pre
   'worg-fortune-insert-javascript-post))

	  

