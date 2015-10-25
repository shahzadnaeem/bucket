
# python -m mimic [options] [<file.in] [>file.out]
#   input:  stdin
#   output: stdout

CMD=python -m mimic

default:
	@echo "make help     # mimic help"
	@echo "make example  # example invocation"
	@echo "make reverse  # reverse invocation"
	@echo
	@echo "to run mimic yourself:"
	@echo "$(CMD) [options] [<file.in] [>file.out]"

help:
	$(CMD) -h

EXAMPLE='word; word; word'

example:
	@echo "Original string: $(EXAMPLE)"
	@echo "mimic'd string: `echo \"$(EXAMPLE)\" | $(CMD) -m100`"

REV_EXAMPLE='worԁ; ᴡоrԁ﹔ wοrԁ'

reverse:
	@echo "mimic'd string: $(REV_EXAMPLE)"
	@echo "Orginal string: `echo \"$(REV_EXAMPLE)\" | $(CMD) -r`"
