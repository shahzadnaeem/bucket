
(setq inhibit-startup-message t)

(set-frame-size (selected-frame)75 50)

(add-hook 'dired-load-hook
  (lambda ()
    (set-variable 'dired-use-ls-dired
      (and (string-match "gnu" system-configuration)
        ;; Only supported for XEmacs >= 21.5 and GNU Emacs >= 21.4 (I think)
        (if (featurep 'xemacs)
          (and
             (fboundp 'emacs-version>=)
               (emacs-version>= 21 5))
          (and (boundp 'emacs-major-version)
               (boundp 'emacs-minor-version)
               (or (> emacs-major-version 21)
                   (and (= emacs-major-version 21)
                        (>= emacs-minor-version 4)))))))))

(cond
 ((string-match "XEmacs" emacs-version)

  (setq load-path (append '("/home/shahzad/lisp/") load-path))

  ;; Display the time in the mode line
  (setq display-time-day-and-date t)
  (display-time)

  ;; Set up scrolling stuff
  (setq scroll-step 16
        next-screen-context-lines 16)

  ;; hideshow
  (load-library "hideshow")

  ;; SVN support - via psvn
  ;;xSN  (require 'psvn)

  (require 'vc)

  ;; Set up some defaults
  (setq-default require-final-newline t
                backup-by-copying-when-mismatch t
                backup-by-copying-when-linked t
                next-line-add-newlines nil
                minibuffer-completion-confirm t
		indent-tabs-mode nil)

  (setq find-file-use-truenames nil
        find-file-compare-truenames t
        minibuffer-confirm-incomplete t
        complex-buffers-menu-p t
        next-line-add-newlines nil
        case-fold-search nil
        case-replace nil
        make-backup-files nil
        default-major-mode 'indented-text-mode
        shell-file-name "/bin/bash"
        require-final-newline t
        indent-tabs-mode nil
        shell-use-extn t
        completion-auto-exit t
        visible-bell t)

  ;;
  ;; Modify the auto mode suffixes...
  ;;
  (setq auto-mode-alist
        (append
          (list
            '("\\.cgi$" . cperl-mode)
            '("\\.t$"   . cperl-mode)
            '("\\.c$"   . c++-mode)
            '("\\.h$"   . c++-mode)
            '("\[Mm\]akefile" . makefile-mode))
          auto-mode-alist))

  (add-to-list 'interpreter-mode-alist '("perl" . cperl-mode))

  ;;
  ;; Mode setups
  ;;
  (defun bc-mode (bc-offset) "Custom c++-mode and c-mode setup"
    (progn
      (hs-minor-mode 1)
;      (setq c-set-style     "linux")
;      (setq c-default-style "linux")
      (setq c-basic-offset bc-offset) ; 2, 4 or as required
      (setq c-offsets-alist
       '(
          (topmost-intro . 0)         ; top level indent
          (substatement-open . 0)     ; extra indent before opening brace
          (substatement . +)          ; extra indent after if or else
          (statement-block-intro . +) ; extra indent on tab
;          (statement-cont . -)        ; extra indent on closing brace
          (statement-cont . 0)        ; extra indent on closing brace
          (defun-block-intro . +)     ; extra indent in function
          (inclass . +)               ; extra indent in class
          (case-label . +)            ; extra indent in case label
          (access-label . -)          ; extra indent in access label
          (statement-case-intro . +)  ; extra indent in case
          (member-init-intro . +)     ; extra indent for member init
          (label . +)                 ; extra indent for labels
          (innamespace . +)           ; extra indent for namespace
        )
      )
      (c-set-offset 'arglist-cont '(c-lineup-arglist-operators 0))
      (c-set-offset 'arglist-cont-nonempty '(c-lineup-arglist-operators c-lineup-arglist))
      (c-set-offset 'arglist-close '(c-lineup-arglist-close-under-paren))
      (setq-default indent-tabs-mode nil) ; use spaces for indent rather than tabs+spaces
      (setq tab-width bc-offset)          ; for existing files that do use tabs
    )
  )

  (defun bc-mode-hook () "parameterised mode hook"
    (progn (bc-mode 2)))

  (defun cperl-mode-hook ()
    (cperl-set-style "C++")
;;    (setq cperl-brace-offset -2)
    (setq cperl-indent-level 2)
    (setq indent-tabs-mode nil)
    )

  (defun sh-mode-hook ()
    (setq sh-basic-offset 2)
    (setq sh-indent-for-then (quote -))
    )

  (setq c-mode-hook     'bc-mode-hook)
  (setq c++-mode-hook   'bc-mode-hook)
  (setq cperl-mode-hook 'cperl-mode-hook)
  (setq sh-mode-hook    'sh-mode-hook)

  (load-library "hideshow")

  ;; Key bindings
  (global-set-key "\C-xh" 'help-command)

  (define-key global-map 'button2 'x-insert-selection)

  (global-set-key 'home "\C-a")
  (global-set-key 'end "\C-e")

  (global-set-key [f1] 'goto-line)

  ;; 'f2 - start recording, '(shift f2) - end recoding, 'f3 replay macro
  (global-set-key 'f2 "\C-x(")
  (global-set-key '(shift f2) "\C-x)")
  (global-set-key 'f3 "\C-xe")

  (global-set-key 'f4 'query-replace)
  (global-set-key '(shift f4) 'query-replace-regexp)

  (global-set-key 'f5 'undo)

  ;; 'f6 - search
  (global-set-key 'f6 'isearch-forward)
  (global-set-key '(shift f6) 'isearch-forward-regexp)

  ;; 'f7 - `other-window'
  (global-set-key 'f7 "\C-xo")
  (global-set-key 'f8 'describe-key)

  ;; 'f10 - 'f13 are sometimes unmarked keypad keys
  (global-set-key 'f9 'set-mark-command)
  (global-set-key 'f10 'kill-ring-save)
  (global-set-key '(shift f10) 'kill-region)
  (global-set-key 'f11 'yank)
  (global-set-key 'f12 'help-for-help)

  (global-set-key "\e\e"         'dabbrev-expand)
  (global-set-key [(control ?/)] 'dabbrev-expand)  ;; Ctrl-/

  (global-set-key 'button4 'scroll-down-command)
  (global-set-key 'button5 'scroll-up-command)

  ;; Remove C-xC-c exit key binding
  (global-unset-key "\C-x\C-c")

  (global-unset-key [(control z)])
  (global-set-key   [(control z)] 'undo)

  ;; The above does not work on newer versions of XEmacs. Then, highjack
  ;; Xemacs’s zap-up-to-char function itself and force it to work as “undo”.
  (defun zap-up-to-char ()
    (interactive)
    (undo)
    )
  )
 )
