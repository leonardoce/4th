(require 'comint)

;; -------------------
;; Cose customizzabili
;; -------------------

(defface leoforth-parsed-word-face
  `((t (:foreground "#d6537a")))
  "*Parole LeoForth che vengono lette da un'altra parola*"
  :group 'leoforth-faces
  :group 'faces)

(defcustom leoforth-interpreter "c:/leonardo/4/prova.exe" "LeoForth interpreter")


;; ------------------
;; Non toccare da qua
;; ------------------

(defvar leoforth-comment-list '("\\ "))

(defvar leoforth-keyword-list '("do" "repeat" "while" "if"
				"then" "loop" "+loop" "else"
				"variable" "array" "value"
				"constant" "does>" "create"
				"only" "also" "definitions"
				"vocabulary"))

(defvar leoforth-font-lock-list '((": [^ ]+" . 'leoforth-parsed-word-face)
				  ("\( [^\(]*\)" . font-lock-comment-face)))

(defvar leoforth-alist '("\\.4th$"))

(defvar leoforth-function-list (list 'leoforth-install-map))

(defvar leoforth-docstring
  "Modo per lavorare il codice 4th")

(defvar leoforth-mode-map
  (let ((map (make-sparse-keymap)))
    (define-key map "\C-c\C-z" 'leoforth-run)
    (define-key map "\C-c\C-l" 'leoforth-load-file)
    map))

(define-generic-mode leoforth-mode 
  leoforth-comment-list
  leoforth-keyword-list 
  leoforth-font-lock-list
  leoforth-alist
  leoforth-function-list
  leoforth-docstring)

(defun leoforth-install-map ()
  (use-local-map leoforth-mode-map))

(defun leoforth-load-file ()
  (interactive)
  (let* ((filename (buffer-file-name (current-buffer)))
	 (load-command (concat "loadfile " filename "\n")))
    (leoforth-run)
    (let ((leoforth-buffer (get-buffer "*leoforth*")))
      (comint-send-string (get-buffer-process leoforth-buffer) load-command))))
	
(defun leoforth-run ()
  (interactive)
  (make-comint "leoforth" leoforth-interpreter)
  (delete-other-windows)
  (switch-to-buffer-other-window "*leoforth*")
  (other-window -1))