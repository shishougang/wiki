;; (require 'org-publish)
;; Modified From meteor1113@newsmth
;; URL: http://blog.csdn.net/meteor1113/archive/2009/07/30/4395673.aspx
;; http://orgmode.org/worg/org-tutorials/org-publish-html-tutorial.html

(setq note-root-dir
      (file-name-directory (or load-file-name (buffer-file-name))))

(setq note-publish-dir
      (expand-file-name "public_html" (directory-file-name
                                       (file-name-directory
                                        (directory-file-name note-root-dir)))))

(unless (boundp 'org-publish-project-alist)
  (setq org-publish-project-alist nil))

(add-to-list 'org-publish-project-alist
      `("wiki-org"
         :base-directory ,note-root-dir
         :publishing-directory ,note-publish-dir
         :base-extension "org"
         :html-head  "<link rel=\"stylesheet\" href=\"./assets/stylesheet.css\" type=\"text/css\"/>"
         :recursive t
         :publishing-function org-html-publish-to-html 
         :auto-index t
;         :index-filename "index.org"
;         :index-title "index"
         :auto-sitemap t                ; Generate sitemap.org automagically...
         :sitemap-filename "index.org"  ; ... call it sitemap.org (it's the default)...
         :sitemap-title "index"         ; ... with title 'sitemap'.
         :link-home "index.html"))

(add-to-list 'org-publish-project-alist
        `("wiki-static"
         :base-directory ,note-root-dir
         :publishing-directory ,note-publish-dir
         :recursive t
         :base-extension "css\\|js\\|png\\|jpg\\|jpeg\\|svg\\|gif\\|pdf\\|mp3\\|swf\\|zip\\|gz\\|txt\\|el\\|tar.gz\\|c\\|cpp\\|sh"
         :publishing-function org-publish-attachment))

(add-to-list 'org-publish-project-alist
      `("octopress" 
          :base-directory "~/Dropbox/Blog/octopress/source/org_posts/"
          :base-extension "org"
          :publishing-directory "~/Dropbox/Blog/octopress/source/_posts/"
          :sub-superscript ""
          :recursive nil
          :publishing-function org-html-publish-to-html 
          :headline-levels 4
          :html-extension "markdown"
          :body-only t))

(add-to-list 'org-publish-project-alist
      `("wiki" 
         :components ("wiki-org" "wiki-static")
         :author "shougangshi@gmail.com"))
