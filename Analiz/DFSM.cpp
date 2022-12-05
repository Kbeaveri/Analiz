#include "DFSM.h"
//Определение следующего состояния
DFSM::state DFSM::getState(const state currState, const symbol currSym) const {
	if (currSym == error) return currState;
	//Переход из текущего состояния по определенному символу
	return matrix[currState][currSym];
}
//Возвращает тип обрабатываемого значения
DFSM::symbol DFSM::getEvent(const char sym) const {
	if (isalpha(sym))
		return letter;
	if (isdigit(sym))
		return digit;
	return error;
}
DFSM::DFSM() : matrix(trans_matrix(4, std::vector<state>(2))) {

	matrix[0][0] = end_id;
	matrix[0][1] = end_intnumber;

	matrix[1][0] = end_id;
	matrix[1][1] = state_3;

	matrix[2][0] = state_3;
	matrix[2][1] = end_intnumber;

	matrix[3][0] = state_3;
	matrix[3][1] = state_3;
}
//Возвращает тип лексемы
type_lexeme DFSM::getTypeLex(const std::string lex) const {
	state currState = start;
	for (char sym : lex) {
		symbol currEvent = getEvent(sym);
		if (currEvent == error) return UNKNOWN;
		currState = getState(currState, currEvent);
	}
	if (currState == end_id)
		return ID;
	if (currState == end_intnumber)
		return INTNUMBER;
	return UNKNOWN;
}
