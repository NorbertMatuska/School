# Author: Norbert Matuška
# Date: 2024-Mar-04
# Goal: Prva bonusova uloha
# Riesenie

#-----------------------------------------------------------------------------
# QUESTION 1)
# MY WORKING: 
setwd("C:\\Users\\matus\\Desktop\\PAS\\bonusova uloha")
# I first read the file into data and then calculate using built in functions
data<-read.csv("C:\\Users\\matus\\Desktop\\PAS\\bonusova uloha\\AlzheimerData.csv")
ageMean<-mean(data$Age)
ageMean
ageMeadian<-median(data$Age)
ageMeadian

cognitionMean<-mean(data$Cognition)
cognitionMean
cognitionMedian<-median(data$Cognition)
cognitionMedian

# MY ANSWER: mean and median are very similar, it suggest symmetric distribution
# mean is not skewed by outliers or extreme values


#-----------------------------------------------------------------------------
# QUESTION 2)
# MY WORKING:
library(ggplot2)
data$AgeCategory<-cut(data$Age, 
                      breaks = c(50,60,70,80,90),
                      labels = c('50-60', '61-70', '71-80', '81-90'),
                      right = FALSE)

ggplot(data, aes(x = AgeCategory, y = Cognition, fill = AgeCategory)) +
  geom_boxplot() +
  labs(title = 'Cognition Scores by Age Category',
       x = 'Age Category',
       y = 'Cognition Score') +
  theme_minimal()

# MY ANSWER: It seems that by increasing age, cognition scores goes up,
# but for the category 50-60, they have higher cognition score than the
# older categories, so there isn't a clear trend of increasing or decreasing
# cognition scores with age based on this plot.

#----------------------------------------------------------------------------


