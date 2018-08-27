# setwd("C://Users//USER//Desktop//Sweave") ### 转换到工作目录，
setwd(getwd())

library(kintr) ###导入kintr程序包

knit("test.Rnw")