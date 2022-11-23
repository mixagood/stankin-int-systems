domains
  surname=symbol
  birthyear=integer
  sex=symbol
  country=symbol

  eventtype=symbol
  date=symbol
  address=symbol

  height=integer
  prize=integer

predicates
  sportsman(surname, birthyear, sex, country).
  event(eventtype, date, address).
  result(surname, eventtype, date, address, height, prize).

  % task 1
  fem_sportsmen_on_event(surname, country, eventtype, date, address).

  % task 2
  prize_won_birthdate(birthyear, prize, surname, birthyear, sex, country).

  % task 3
  sportsmen_country_height_event_data(country, height, eventtype, date, address, surname, birthyear, sex, country).

  % task 4
  same_year_events(date, eventtype, date, address).
  
clauses
  sportsman(ivanov, 1984, m, russia).
  sportsman(petrova, 1964, f, russia).
  sportsman(rogers, 1974, m, usa).
  sportsman(potter, 1994, f, usa).
  sportsman(sholtz, 1964, f, germany).
  sportsman(truss, 1994, f, uk).
  
  event(olympics, "2012", london).
  event(olympics, "2016", rio).
  event(common, "2012", moscow).
  
  result(ivanov, olympics, "2012", london, 310, 1).
  result(ivanov, olympics, "2016", rio, 298, 3).
  result(ivanov, common, "2012", moscow, 300, 2).

  result(potter, olympics, "2012", london, 300, 1).  
  result(petrova, olympics, "2012", london, 290, 2).
  
  result(petrova, common, "2012", moscow, 300, 1).
  result(potter, common, "2012", moscow, 290, 2).
  result(sholtz, common, "2012", moscow, 280, 3).

  result(truss, olympics, "2016", rio, 410, 1).
  result(potter, olympics, "2016", rio, 400, 2).
  result(petrova, olympics, "2016", rio, 390, 3).
  result(sholtz, olympics, "2016", rio, 350, 4).
  
  fem_sportsmen_on_event(SURNAME, COUNTRY, EVENTTYPE, DATE, ADDRESS):-result(SURNAME, EVENTTYPE, DATE, ADDRESS, _, _), sportsman(SURNAME, _, f, COUNTRY).
  
  prize_won_birthdate(BIRTHYEAR, PRIZE, SURNAME, BIRTHYEAR1, SEX, COUNTRY):- result(SURNAME, _, _, _, _, PRIZE), sportsman(SURNAME, BIRTHYEAR1, SEX, COUNTRY), BIRTHYEAR1 < BIRTHYEAR.
  
  sportsmen_country_height_event_data(COUNTRY, HEIGHT, EVENTTYPE, DATE, ADDRESS, SURNAME, BIRTHYEAR, SEX, COUNTRY) :- result(SURNAME, EVENTTYPE, DATE, ADDRESS, HEIGHT1, _), HEIGHT1 >= HEIGHT, sportsman(SURNAME, BIRTHYEAR, SEX, COUNTRY).
  
  same_year_events(YEAR, EVENTTYPE, YEAR, ADDRESS) :- event(EVENTTYPE, YEAR, ADDRESS).

goal
  %fem_sportsmen_on_event(SURNAME, COUNTRY, olympics, "2012", london).
  %prize_won_birthdate(1980, 1, SURNAME, BIRTHDATE, SEX, COUNTRY).
  %sportsmen_country_height_event_data(russia, 200, olympics, "2012", london, SURNAME, BIRTHYEAR, SEX, COUNTRY).
  same_year_events("2012", EVENTTYPE, DATE, ADDRESS).
  