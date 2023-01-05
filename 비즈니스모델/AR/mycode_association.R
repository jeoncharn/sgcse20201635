##### association analysis
setwd("c:/Rtest")

install.packages("arules")
library(arules)

result <- read.transactions("mydata_association.csv", format="basket", sep=",")
result

as(result, "data.frame")

rules=apriori(result, parameter=list(supp=0.1, conf=0.1))
inspect(rules)

rules=apriori(result, parameter=list(supp=0.3, conf=0.1))
inspect(rules)

