#title:"cvicenie 2"
#meno:"Norbert Matuska"
#datum: 19.02.2024

#nastavenie adresara
setwd("C:\\Users\\matus\\Desktop\\PAS")
getwd()
library(Matrix)
# sqrt() vie robit iba druhu odmocninu
a<-3
class(a)
b<-4L # velke L je integer
class(b)
z<-2+3i
class(z)

# zmena datoveho typu
d<-as.integer(a)
is.integer(d)
d

# logicke operatory
3>7
5==5
4!=5

# Data structures
v1<-c(2,3,4)
v2<-c(1,0,2)
v1+v2 #scitanie vektorov
v1*v2
v1%*%v2 #skalarne nasobanie
v1*c(1,2) #treba davat bacha na dlzku
length(v1)
v3<-2:24 # vektor zadany postupnostou, cize od 2 po 24 naplni po kroku 1
v3
v4<-seq(from=2,to=24,by=3)
v4
v5<-rep(v1,times=4) # zreplikuj vektor1 4x  za sebou
v5
rep(v1,times=c(3,2,5)) # kolkokrat sa bude dana suradnica opakovat
sum(v4) # sucet vsetkych prvkov vo vektore
prod(v1) # sucin vsetkych prvkov vo vektore
sum(v4[3:7])
cumsum(v1) # kumulovany sucet UwU

# matice
v6<-v3[1:12]
v6

A<-Matrix(v6,4,3) # matica z v6 vektora zapisana na 4x3 maticu
A
B<-Matrix(v6,4,3,byrow=T)
B

#transponovana matica
t(B)
#vyber prvku z matice
B[2,3]
#vyber podpola, podmatice
B[1:2,2:3]

#data.frame, datovy ramec
meno=c("Ala","Jojo","Jana","Palo","Miro","Eva")
vek=c(14,16,14,17,15,13)
deti=data.frame(meno,vek)
deti
#pridanie parametra do datoveho ramca
deti$test=c(10,11,15,14,12,10)
deti
#pridanie neciselneho parametra a pouzitie prikazu faktor
deti$pohlavie=factor(c(1,0,1,0,0,1), labels=c("m","z"))
deti

#filtrovanie dat
zeny<-subset(deti,deti$pohlavie=="z")
zeny

min(deti$vek)
max(deti$test)
mean(deti$test) #aritmeticky priemer z testu
var(deti$test) #odchylka kvadrantu, o kolko sa v kvadrante deti lisili
summary(deti)

# ------------------------------------
# kreslenie
# ------------------------------------
library(MASS)
library(ggplot2)
k<-rep(v1, times=c(3,2,5))
a<-barplot(k)
a<-barplot(table(k)) #na diskretne data/graf hustoty
w<-seq(0,5,0.4)
hist(w) #histogram pre spojite data
pie(table(k)) #kolacovy diagram
