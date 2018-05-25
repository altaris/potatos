CPPLINT   		= tools/cpplint.py
CPPLINTFILTERS 	= -legal/copyright,-runtime/int,-whitespace/indent

doc:
	@doxygen doxyfile

lint:
	@python3 $(CPPLINT) --quiet --filter=$(CPPLINTFILTERS) --extensions=c,cpp --recursive src/
	@python3 $(CPPLINT) --quiet --filter=$(CPPLINTFILTERS),-whitespace/blank_line --extensions=h,hpp --recursive src/
