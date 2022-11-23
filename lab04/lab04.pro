domains
  list = integer*
  int=integer
  intl=integer*

predicates
  numbers(list).
  addfirst(integer, list, list).
  append(list, list, list).
  delete(integer, list, list).
  member(integer, list).
  last(list, integer).

  del_elt(int,list,list)
  uniq(list,list)
  intersection(list, list, list).

clauses
  numbers([]):-!.
  numbers(L):-L = [H|T], write(H), numbers(T).
  
  addfirst(X, L, [X | L]).
  
  append([], List2, List2):-!.
  append([H|T], List2, [H|TRes]):-append(T, List2, TRes).
  
  delete(_Elem, [], []).
  delete(Elem, [Elem|T], TRes):-delete(Elem, T, TRes).
  delete(Elem, [H|T], [H|TRes]):-delete(Elem, T, TRes).
  
  member(Elem, [Elem|_T]).
  member(Elem, [_H|T]):-member(Elem, T).
  
  last([H|[]], H).
  last([_|T], LAST):-last(T, LAST).
  
  
  del_elt(_,[],[]).
  del_elt(X,[X|T],R) :- del_elt(X,T,R).
  del_elt(X,[Y|T],[Y|R]) :-  X<>Y,del_elt(X,T,R).
 
  uniq([],[]).
  uniq([X|T],[X|R]) :- del_elt(X,T,Y), uniq(Y,R).
  
  intersection([],_,[]).
  intersection([H|L1],L2,[H|L]):- member(H,L2), !, intersection(L1,L2,L). 
  intersection([_|L1],L2,L):- intersection(L1,L2,L).

goal
  %numbers([1, 2, 3, 4]).
  %addfirst(5, [1, 2, 3, 4], LIST).
  %append([1, 2, 3], [4, 5, 6], LIST).
  %delete(3, [1, 2, 3, 4, 3, 5], LIST).
  %member(2, [1, 2, 3, 4]).
  %last([1, 2, 3], X).
  %uniq([1, 2, 2, 3, 4, 1], LIST).  
  intersection([1, 2, 3, 4], [0, 2, 4, 6], SET).
