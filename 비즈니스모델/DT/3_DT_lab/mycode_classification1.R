##### classification analysis

setwd("c:/Rtest")

install.packages("party")
library(party)

result <- read.csv("mydata_classification.csv", header=FALSE)
View(result)

install.packages("reshape")
library(reshape)

result <- rename(result, c(V1="total", V2="price", V3="period", V4="variety", V5="response"))
View(result)

set.seed(1234)

resultsplit <- sample(2, nrow(result), replace=TRUE, prob=c(0.7, 0.3))
trainD <- result[resultsplit==1,]
testD <- result[resultsplit==2,]

rawD <- response ~ total + price + period+ variety
trainModel <- ctree(rawD, data=trainD)

table(predict(trainModel), trainD$response)
print(trainModel)

plot(trainModel)
plot(trainModel, type="simple")

testModel <- predict(trainModel, newdata=testD)
table(testModel, testD$response)
