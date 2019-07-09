#!/usr/bin/env Rscript
suppressMessages(library(DoE.base))
suppressMessages(library(readr))
suppressMessages(library(dplyr))

options(crayon.enabled = FALSE) 
options(readr.show_progress = FALSE)

DoE <- fac.design(factor.names=list(
			mapping=c("os", "homo", "hetero"),
			appA=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:8192", "load-ind:16", "load-ind:8192", "load-rand:16", "load-rand:8192", "store-ind:16", "store-ind:8192", "store-rand:16", "store-rand:8192"),
			appB=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:8192", "load-ind:16", "load-ind:8192", "load-rand:16", "load-rand:8192", "store-ind:16", "store-ind:8192", "store-rand:16", "store-rand:8192")
		))

write_csv(DoE, "DoE.alegrete.csv", col_names=FALSE)