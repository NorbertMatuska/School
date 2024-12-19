# cvicenie 3

setwd("C:\\Users\\matus\\Desktop\\PAS")

library(ggplot2)
library(lattice)
library(PASWR2)
# 12.a)
Nationality<-c("German","French","British","American","Rest of the world")
Year<-c("2003","2004","2005")

tourists<-matrix(c(9.303,9.536,9.918,
                   7.959,7.736,8.875,
                   15.224,15.629,16.090,
                   0.905,0.894,0.883,
                   17.463,18.635,20.148),byrow=TRUE,nrow=5)

dimnames(tourists)<-list(Nationality, Year)
tourists
# 12.b)
apply(tourists,1,sum) #sucet riadkov dimenzia 1
# 12.c)
apply(tourists,2,sum) #sucet stlpcov dimenzia 2


# 13.
# priklad na for loop
sum.a <- 0
for(i in c(10,20,30)){
  sum.a<-i+sum.a
  print(sum.a)
}
sum.a

for(celsius in seq(18,28,2)){
  print(c(celsius,9/5*celsius+32))
}

# 4.a)
quantile(WHEATUSA2004$acres)
quantile(WHEATUSA2004$acres,probs=seq(0,1,0.1))
mean(WHEATUSA2004$acres) # aritmeticky priemer
IQR(WHEATUSA2004$acres) # interkvartilove rozpatie
var(WHEATUSA2004$acres) # variancia/rozptyl
sd(WHEATUSA2004$acres) # standardna odchylka
sum(WHEATUSA2004$acres) # suma
summary(WHEATUSA2004$acres) # 

# 4.b)
bottom20<-quantile(WHEATUSA2004$acres, probs=0.20)
bottom20
WHEATUSA2004[WHEATUSA2004$acres<bottom20,]
top20<-quantile(WHEATUSA2004$acres, probs=0.80)
top20
WHEATUSA2004[WHEATUSA2004$acres>top20,]

WHEATUSA2004[order(WHEATUSA2004$acres),]

which(WHEATUSA2004[order(WHEATUSA2004$acres),]$states=="WI")
length(WHEATUSA2004$acres)
pk<-(9-1)/(30-1)
pk
quantile(WHEATUSA2004$acres, probs=pk)


# 4.c)
p1<-ggplot(WHEATUSA2004, aes(x=acres))+geom_histogram()+theme_bw()
p2<-ggplot(WHEATUSA2004,aes(x=acres,y=..density..)) + geom_histogram() + geom_density()
multiplot(p1,p2)

# 4.d)
p1<-ggplot(WHEATUSA2004, aes(x=acres))+geom_histogram()+theme_bw()
p2<-ggplot(WHEATUSA2004,aes(x=acres,y=..density..)) + geom_histogram() + 
  geom_density() + geom_density(color = 'darkred', linewidth=1)
multiplot(p1,p2)


# 5.a)
VIT2005

VIT2005$out<-factor(VIT2005$out,  level=c("E25", "E50", "E75", "E100"))
levels(VIT2005$out)
xtabs(~out,data=VIT2005)


# 5.b)
ggplot(data=VIT2005,aes(x=totalprice)) + geom_histogram()+theme_bw()

max(VIT2005$totalprice)
summary(VIT2005$totalprice)
IQR(VIT2005$totalprice)

# 5.c)
ggplot(data=VIT2005,aes(x=area, y=totalprice))+geom_point()+theme_bw()

# 5.d)
xyplot(totalprice~area|toilets,data=VIT2005,layout=c(1,2),as.table=TRUE)
TEXT<-"Number of\ntoilet"
ggplot(data=VIT2005,aes(x=area,y=totalprice,color=as.factor(toilets)))+
  geom_point()+facet_grid(toilets ~.)+theme_bw()+guides(color=guide_legend(TEXT))

# 5.e)
b<-subset(VIT2005,subset=area >=80&area<=100)
ANS<-tapply(b$totalprice, b$toilets, median)
ANS
diff(ANS)
