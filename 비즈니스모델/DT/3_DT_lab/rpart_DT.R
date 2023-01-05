##### classification analysis

setwd("c:/Rtest")
install.packages("rpart")
library(rpart)
install.packages("rpart.plot")
library(rpart.plot)

result <- read.csv("mydata_classification2.csv", header=TRUE)
View(result)

set.seed(1234)

resultsplit <- sample(2, nrow(result), replace=TRUE, prob=c(0.7, 0.3))
trainD <- result[resultsplit==1,]
testD <- result[resultsplit==2,]

trainModel <- rpart(response~. , data=trainD)

print(trainModel)

rpart.plot(trainModel)
