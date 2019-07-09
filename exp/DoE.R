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
			appA=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain2", "dep-chain3", "dep-chain4", "dep-chain5", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:32", "load-dep:64", "load-dep:128", "load-dep:256", "load-dep:512", "load-dep:1024", "load-dep:2048", "load-dep:4096", "load-dep:8192", "load-dep:16384", "load-dep:32768", "load-dep:65536", "load-ind:16", "load-ind:32", "load-ind:64", "load-ind:128", "load-ind:256", "load-ind:512", "load-ind:1024", "load-ind:2048", "load-ind:4096", "load-ind:8192", "load-ind:16384", "load-ind:32768", "load-ind:65536", "load-rand:16", "load-rand:32", "load-rand:64", "load-rand:128", "load-rand:256", "load-rand:512", "load-rand:1024", "load-rand:2048", "load-rand:4096", "load-rand:8192", "load-rand:16384", "load-rand:32768", "load-rand:65536", "store-ind:16", "store-ind:32", "store-ind:64", "store-ind:128", "store-ind:256", "store-ind:512", "store-ind:1024", "store-ind:2048", "store-ind:4096", "store-ind:8192", "store-ind:16384", "store-ind:32768", "store-ind:65536", "store-rand:16", "store-rand:32", "store-rand:64", "store-rand:128", "store-rand:256", "store-rand:512", "store-rand:1024", "store-rand:2048", "store-rand:4096", "store-rand:8192", "store-rand:16384", "store-rand:32768", "store-rand:65536"),
			appB=c("ctl-complex", "ctl-conditional", "ctl-random", "ctl-small-bbl", "ctl-switch", "dep-chain1", "dep-chain2", "dep-chain3", "dep-chain4", "dep-chain5", "dep-chain6", "fp-add", "fp-div", "fp-mul", "int-add", "int-div", "int-mul", "load-dep:16", "load-dep:32", "load-dep:64", "load-dep:128", "load-dep:256", "load-dep:512", "load-dep:1024", "load-dep:2048", "load-dep:4096", "load-dep:8192", "load-dep:16384", "load-dep:32768", "load-dep:65536", "load-ind:16", "load-ind:32", "load-ind:64", "load-ind:128", "load-ind:256", "load-ind:512", "load-ind:1024", "load-ind:2048", "load-ind:4096", "load-ind:8192", "load-ind:16384", "load-ind:32768", "load-ind:65536", "load-rand:16", "load-rand:32", "load-rand:64", "load-rand:128", "load-rand:256", "load-rand:512", "load-rand:1024", "load-rand:2048", "load-rand:4096", "load-rand:8192", "load-rand:16384", "load-rand:32768", "load-rand:65536", "store-ind:16", "store-ind:32", "store-ind:64", "store-ind:128", "store-ind:256", "store-ind:512", "store-ind:1024", "store-ind:2048", "store-ind:4096", "store-ind:8192", "store-ind:16384", "store-ind:32768", "store-ind:65536", "store-rand:16", "store-rand:32", "store-rand:64", "store-rand:128", "store-rand:256", "store-rand:512", "store-rand:1024", "store-rand:2048", "store-rand:4096", "store-rand:8192", "store-rand:16384", "store-rand:32768", "store-rand:65536")
		))

write_csv(DoE, paste("DoE.", ".csv", sep=args[1]), col_names=FALSE)