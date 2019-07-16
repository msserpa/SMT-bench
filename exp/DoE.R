#!/usr/bin/env Rscript
suppressMessages(library(DoE.base))
suppressMessages(library(readr))
suppressMessages(library(dplyr))

options(crayon.enabled = FALSE) 
options(readr.show_progress = FALSE)

args = commandArgs(trailingOnly=TRUE)
if(length(args) == 0){
  stop("at least one argument must be supplied (execution step)")
}

DoE <- fac.design(factor.names=list(
			mapping=c("os", "homo", "hetero", "rand"),
                        appA=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain2", "dep-chain3", "dep-chain4", "dep-chain5", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:32", "load-dep:64", "load-dep:8192", "load-ind:16", "load-ind:32", "load-ind:64", "load-ind:8192", "load-rand:16", "load-rand:32", "load-rand:64", "load-rand:8192", "store-ind:16", "store-ind:32", "store-ind:64", "store-ind:128","store-ind:8192", "store-rand:16", "store-rand:32", "store-rand:64", "store-rand:128", "store-rand:8192"),
			appB=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain2", "dep-chain3", "dep-chain4", "dep-chain5", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:32", "load-dep:64", "load-dep:8192", "load-ind:16", "load-ind:32", "load-ind:64", "load-ind:8192", "load-rand:16", "load-rand:32", "load-rand:64", "load-rand:8192", "store-ind:16", "store-ind:32", "store-ind:64", "store-ind:128","store-ind:8192", "store-rand:16", "store-rand:32", "store-rand:64", "store-rand:128", "store-rand:8192")
		))

write_csv(DoE, paste("DoE.", ".csv", sep=args[1]), col_names=FALSE)
