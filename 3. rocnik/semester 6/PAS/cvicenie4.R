# cvicenie 4
# Norbert Matuška
# kombinatorika

setwd("C:\\Users\\matus\\Desktop\\PAS")

# zalezi na poradi?
#       / \
#  ano /   \ nie        kombinacie
#                   opakuju sa prvky?
#                              / \
#                         ano /   \ nie
#           C'(n)=(n-1 over k-1)   C(n) =( n over k) = n!/((n-k)!*k!)

choose(90,8)

choose(6,2)*choose(7,2)*choose(10,3)*choose(5,3)

# kolko roznych usporiadani pismen mozno urobit z pismenok:
# BIOLOGY, PROBABILITY, STATISTICS
# pre BIOLOGY P1,1,2,1,1,1(7) -> 7 prvkov a tie cisla predtym su pocet vyskytov
factorial(7)/factorial(2)

# triatlonovy klub tvori 11 zien a 7 muzov. Aka je pravdepodobnost ze komisia
# vyberie prave styroch s presne tromi zenami
(choose(11,3)*choose(7,1)/choose(18,4))*100
# 37,75%
