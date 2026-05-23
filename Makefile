

all:
	@python -m poredec --tasks benchmarks/tasks.csv
.PHONY: dist

cfg:
	@python -m poredec --tasks benchmarks/tasks.csv --cfg
.PHONY: cfg
