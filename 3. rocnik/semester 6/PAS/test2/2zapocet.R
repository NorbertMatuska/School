# 2. zapoctova pisomka

library(lattice)
library(ggplot2) 
library(PASWR2)

# 1
# mean = 0.66, sd = 0.017, X < 0.65
round(pnorm(0.65, 0.66, 0.017), 3)

# 2
# E[X] = 72, E[Y] = 162, Var[X] = 49, Var[Y] = 49, E[XY] = 11700
covariance = 11700 - 72*162
covariance
# independent when cov[x,y] = 0
# cov[x,y] > 0 

# 3 
# 4 = 20
# 5 = x
ppois(20, 4, lower.tail = FALSE)
ppois(10, 5, lower.tail = FALSE)


# 4
round(sum(dbinom(7:9, 10, 0.8)), 3)

# 5
pop1 = c(22, 25, 27, 31)
srs(pop1, 2)
expand.grid(pop1, pop1)

# 6
# consumption N(85, 10)
# generated N(90, 15)
round(dexp(pnorm(85, 90, 10, lower.tail = FALSE)), 3)

# 7

# 8
set.seed(888)
sd(sample(10000, 1000, 0.2))


# 9 
round(ppois(3,5, lower.tail = FALSE), 3)

# 10
pnorm(50, 50, 5, lower.tail = FALSE)
pnorm(45, 45, 6, lower.tail = FALSE)
pnorm(130, 130, 13, lower.tail = FALSE)
