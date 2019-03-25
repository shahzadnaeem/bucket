(custom-set-variables
 '(blink-cursor-mode t nil (blink-cursor))
 '(column-number-mode t)
 '(default-toolbar-position 'left)
 '(font-lock-mode t nil (font-lock))
 '(gutter-buffers-tab-visible-p t)
 '(line-number-mode t)
 '(paren-mode 'sexp nil (paren))
 '(require-final-newline 'ask)
 '(toolbar-visible-p nil))

(custom-set-faces
 '(default ((t (:background "Snow" :size "18pt" :family "Nimbus Mono L"))) t)
 '(cperl-array-face ((((class color) (background light)) (:foreground "Blue" :background "lightyellow2"))))
 '(cperl-hash-face ((((class color) (background light)) (:foreground "Red" :background "lightyellow2"))))
 '(dired-face-directory ((((type x pm mswindows tty) (class color)) (:family "fixed"))))
 '(font-lock-comment-face ((((class color) (background light)) (:foreground "#B89166"))))
 '(zmacs-region ((t (:foreground "#0" :background "#ffffff"))) t))
