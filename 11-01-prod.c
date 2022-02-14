/*
Scrivere due programmi in C (produttore &
consumatore) che una volta agganciati alla stessa
memoria condivisa, operano su di essa in maniera
esclusiva tramite l’utilizzo di semafori (System V).
Più precisamente il consumatore dovrà attendere il
completamento della scrittura sulla memoria da parte del
produttore, che a sua volta attenderà il consumatore
affinchè abbia effettivamente completato la lettura.
Il produttore prende il dato da stdin, mentre il
consumatore stampa il dato a stdout.
*/