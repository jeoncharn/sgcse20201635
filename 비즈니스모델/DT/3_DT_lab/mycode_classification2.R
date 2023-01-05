##### classification analysis

setwd("c:/Rtest")

install.packages("party")
library(party)

result <- read.csv("mydata_classification2.csv", header=TRUE)
View(result)



set.seed(1234)

resultsplit <- sample(2, nrow(result), replace=TRUE, prob=c(0.7, 0.3))
trainD <- result[resultsplit==1,]
testD <- result[resultsplit==2,]

trainModel <- ctree(response~. , data=trainD)

table(predict(trainModel), trainD$response)
print(trainModel)

plot(trainModel)
plot(trainModel, type="simple")

testModel <- predict(trainModel, newdata=testD)
table(testModel, testD$response)
