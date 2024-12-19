setwd("C:\\Users\\matus\\Desktop\\PAS")

countby5<-seq(from=5,to=100,by=5)
countby5

Treatment<-rep(c("Treatment One", "Treatment Two", "Treatment Three"),
               c(20, 18, 22))
Treatment
xtabs(~Treatment)

rep(seq(from=20,to=5,by=-5),1:4)

x=5
y=7
z=x^y
z

u<-c(1,2,5,4)
v=c(2,2,1,1)

choose(90, 8)

choose(6,2)*choose(7,2)*choose(10,3)*choose(5,3)

# BIOLOGY
# 2x O, 1x B, I, L, G, Y
factorial(7)/factorial(2)

# PROBABILITY
# 2x B, I 1x P R O A L T Y
factorial(11)/(factorial(2)*factorial(2))

(choose(11,3)*choose(7,1))/choose(18,4)

(1-5)*0.5+(30-5)*0.05
10000*0.01+1000*0.05+0*0.94
f<-function(x) 2*exp(-2*x)
integrate(f,0,60)

library(ggplot2)
library(MASS)
help(lqs, MASS)
library()

p1<-ggplot(data=Cars93, aes(x=Min.Price, y=..density..)) + 
  geom_histogram(fill="red") + theme_bw()
p1

p2<-ggplot(data=Cars93, aes(x=Max.Price, y=..density..)) + 
  geom_histogram(fill="green") + theme_bw()
p2

p3<-ggplot(data=Cars93, aes(x=Weight, y=..density..)) + 
  geom_histogram(fill="blue") + theme_bw()
p3

p4<-ggplot(data=Cars93, aes(x=Length, y=..density..)) + 
  geom_histogram(fill="cyan") + theme_bw() + geom_density(color="black")
p4

multiplot(p1,p2,p3,p4, cols=2)

library(lattice)

bwplot(Cars93$Price ~ Cars93$DriveTrain | Type, data = Cars93, as.table=TRUE)

ggplot(data=Cars93, aes(x=DriveTrain, y=Price)) + 
  geom_boxplot() + facet_wrap(~ Type) + theme_bw()

library(PASWR2)

quantile(WHEATSPAIN$hectares)
quantile(WHEATSPAIN$hectares,probs=seq(0,1,0.1))

mean(WHEATSPAIN$hectares)
max(WHEATSPAIN$hectares)
min(WHEATSPAIN$hectares)
IQR(WHEATSPAIN$hectares)
var(WHEATSPAIN$hectares)
sd(WHEATSPAIN$hectares)
sum(WHEATSPAIN$hectares)

x<-function(x, ...){
  print(c(Quantiles=quantile(x), Mean=mean(x),Var=var(x),SD=sd(x),Total=sum(x),
          Range=diff(range(x))))
}
x(WHEATSPAIN$hectares)

bottom<-quantile(WHEATSPAIN$hectares, probs=0.1)
top<-quantile(WHEATSPAIN$hectares, probs=0.9)

WHEATSPAIN[WHEATSPAIN$hectares < bottom,]
WHEATSPAIN[WHEATSPAIN$hectares > top,]

help(quantile)

x1<-ggplot(data=WHEATSPAIN, aes(x=acres)) + geom_histogram() + theme_bw()
x2<-ggplot(data=WHEATSPAIN, aes(x=acres, y=..density..)) + geom_histogram() + 
  theme_bw() + geom_density()

multiplot(x1,x2)

vcbins<-c(0,100000, 250000, 360000, 1550000)
WHEATSPAIN$cuts<-cut(WHEATSPAIN$acres, breaks = vcbins)
x3<-ggplot(data=WHEATSPAIN, aes(x=acres,y=..density..)) + 
  geom_histogram(breaks=vcbins) + theme_bw() + geom_density()
x4<-ggplot(data=WHEATSPAIN, aes(x=cuts)) + 
  theme_bw() + geom_bar()

multiplot(x3,x4)

x5<-ggplot(data=WHEATSPAIN, aes(x=acres,y=..density..)) + 
  geom_vline(xintercept = mean(WHEATSPAIN$acres)) + geom_vline(xintercept = median(WHEATSPAIN$acres)) +
  geom_histogram() + theme_bw()
x5

x6<-ggplot(data=WHEATSPAIN, aes(x=hectares)) + geom_boxplot() + theme_bw() + 
  identify(WHEATSPAIN$community)
x6
with(data = WHEATSPAIN, boxplot(hectares))
with(data = WHEATSPAIN, identify(rep(1, length(hectares)), hectares, labels=community))

head(WHEATSPAIN[order(WHEATSPAIN$hectares, decreasing = TRUE),])
WHEAT2<-WHEATSPAIN[WHEATSPAIN$community != "Castilla-Leon",]
head(WHEAT2[order(WHEATSPAIN$hectares, decreasing = TRUE),])

mean(WHEATSPAIN$hectares)
mean(WHEAT2$hectares)

median(WHEATSPAIN$hectares)
median(WHEAT2$hectares)

sd(WHEATSPAIN$hectares)
sd(WHEAT2$hectares)


Nationality<-c("German","French","British","American","Rest of the world")
Year<-c("2003","2004","2005")

tourists<-matrix(c(9.303,9.536,9.918,
                   7.959,7.736,8.875,
                   15.224,15.629,16.090,
                   0.905,0.894,0.883,
                   17.463,18.635,20.148),byrow=TRUE,nrow=5)
tourists
dimnames(tourists)<-list(Nationality, Year)
tourists
apply(tourists, 1, sum)
apply(tourists, 2, sum)

quantile(WHEATUSA2004$acres)
quantile(WHEATUSA2004$acres, probs=seq(from=0,to=1,by=0.1))
mean(WHEATUSA2004$acres)
max(WHEATUSA2004$acres)
min(WHEATUSA2004$acres)
IQR(WHEATUSA2004$acres)
var(WHEATUSA2004$acres)
sd(WHEATUSA2004$acres)
sum(WHEATUSA2004$acres)

bottom20<-quantile(WHEATUSA2004$acres, probs=0.2)
bottom20
top20<-quantile(WHEATUSA2004$acres, probs=0.8)
top20
WHEATUSA2004[WHEATUSA2004$acres > top20,]
quantile(WHEATUSA2004$acres, probs=(which(WHEATUSA2004[order(WHEATUSA2004$acres),]$states == "WI") - 1)/(30-1))

h<-ggplot(data = WHEATUSA2004, aes(x=acres)) + geom_histogram() + theme_bw()
h2<-ggplot(data = WHEATUSA2004, aes(x=acres, y=..density..)) + geom_histogram() + geom_density() + theme_bw()
multiplot(h,h2)
