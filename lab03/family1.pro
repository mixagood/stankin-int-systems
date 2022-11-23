domains 
  name=symbol
  
predicates
  man(name).
  woman(name).
  parent(name, name).
  child(name, name).
  married(name, name).
  
  mother(name, name).
  father(name, name).
  
  son(name, name).
  daughter(name, name).
  
  uncle(name, name).
  
  grandmother(name, name).
  nephew(name, name).
  wifes_mother(name, name).
  husband_of_daughter(name, name).
  
clauses
  man(alexey).
  man(andrey).
  man(oleg).
  man(mikhail).
  man(nikita).
  
  woman(anna).
  woman(natalia).
  woman(oksana).
  woman(maria).
  woman(polina).
  
  child(mikhail, oleg).
  child(mikhail, oksana).
  child(maria, oleg).
  child(maria, oksana).
  child(oksana, anna).
  child(oksana, alexey).
  child(oleg, andrey).
  child(oleg, natalia).
  child(nikita, andrey).
  child(nikita, natalia).
  
  parent(oleg, mikhail).
  parent(oksana, mikhail).
  parent(oleg, maria).
  parent(oksana, maria).
  parent(anna, oksana).
  parent(alexey, oksana).
  parent(andrey, oleg).
  parent(natalia, oleg).
  parent(andrey, nikita).
  parent(natalia, nikita).
  
  married(anna, alexey).
  married(alexey, anna).
  married(andrey, natalia).
  married(natalia, andrey).
  married(oksana, oleg).
  married(oleg, oksana).
  married(nikita, polina).
  married(polina, nikita).
  
  mother(NAME1, NAME2):-parent(NAME1, NAME2), woman(NAME1).
  father(NAME1, NAME2):-parent(NAME1, NAME2), man(NAME1).
  son(NAME1, NAME2):-child(NAME1, NAME2), man(NAME1).
  daughter(NAME1, NAME2):-child(NAME1, NAME2), woman(NAME1).
  
  uncle(FIND, NAME) :- parent(X, NAME), parent(Y, X), son(FIND, Y), FIND <> X.
  
  grandmother(FIND, NAME):- parent(X, NAME), mother(FIND, X).
  
  nephew(FIND, NAME) :- parent(X, NAME), son(Y, X), Y <> NAME, son(FIND, Y).
  
  wifes_mother(FIND, NAME) :- married(NAME, X), woman(X), mother(FIND, X), !.
  
  husband_of_daughter(FIND, NAME):-daughter(X, NAME), married(FIND, X).
  
goal
  %grandmother(FIND, mikhail).
  %nephew(FIND, nikita).
  %wifes_mother(FIND, oleg).
  husband_of_daughter(FIND, alexey).
  
  