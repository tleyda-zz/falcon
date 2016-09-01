SUBDIRS = src tests

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	make -C $@

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done
	rm testromancalc
