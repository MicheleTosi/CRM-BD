#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

static void view_customer(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char cf[17];
	printf("\nTax code: ");
	getInput(17, cf, false);



	
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_cliente(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize customer statement\n", false);
	}

	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = conf.username;
	param[1].buffer_length = strlen(conf.username);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for customer\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve customer\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nCustomer personal data");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_societa(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize company list statement\n", false);
	}



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for company list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve company list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nCompany of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_indirizzo(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize address list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for address list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve address list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of address of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_telefono(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize telephone list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for telephone list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve telephone list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of telephone of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_fax(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize fax list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for fax list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve fax list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of fax of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_mail(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize mail list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for mail list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve mail list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of mail of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_note(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize note list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for note list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve note list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of note of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_accettate(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize accepted proposal list statement\n", false);
	}

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for accepted proposal list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve accepted proposal list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of accepted proposal of selected customer");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
}

static void add_appointment(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[9];

	char cf[17];
	char num_sala[3];
	int num;
	char via_sede[46];
	char civico_sede[6];
	char citta_sede[46];
	char codice_proposta[10];
	char anno[5];
	char mese[3];
	char giorno[3];
	char ora[3];
	char minuti[3];
	MYSQL_TIME data, inzio, fine;
	memset(&data,0, sizeof(data));
	memset(&inzio,0, sizeof(inzio));
	memset(&fine,0, sizeof(fine));

	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Room number: ");
	getInput(3, num_sala, false);
	num=atoi(num_sala);
	printf("Address: ");
	printf("\nStreet: ");
	getInput(46, via_sede, false);
	printf("Street number: ");
	getInput(6, civico_sede, false);
	printf("City: ");
	getInput(46, citta_sede, false);
	printf("Proposal ID: ");
	getInput(10, codice_proposta, false);
	printf("Date and hour: ");
	printf("\nDay: ");
	getInput(3, giorno, false);
	printf("Month: ");
	getInput(3, mese, false);
	printf("Year: ");
	getInput(5, anno, false);
	printf("Start hour: ");
	getInput(3, ora, false);
	printf("Start minute: ");
	getInput(3, minuti, false);

	data.day=atoi(giorno);
	data.month=atoi(mese);
	data.year=atoi(anno);
	inzio.hour=atoi(ora);
	inzio.minute=atoi(minuti);

	printf("End hour: ");
	getInput(3, ora, false);
	printf("End minute: ");
	getInput(3, minuti, false);	

	fine.hour=atoi(ora);
	fine.minute=atoi(minuti);

	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_appuntamento(?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize customers list statement\n", false);
	}

	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &num;
	param[1].buffer_length = sizeof(num);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = via_sede;
	param[2].buffer_length = strlen(via_sede);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = civico_sede;
	param[3].buffer_length = strlen(civico_sede);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = citta_sede;
	param[4].buffer_length = strlen(citta_sede);

	param[5].buffer_type = MYSQL_TYPE_DATE;
	param[5].buffer = (char *)&data;
	param[5].buffer_length = sizeof(data);

	param[6].buffer_type = MYSQL_TYPE_TIME;
	param[6].buffer = (char *)&inzio;
	param[6].buffer_length = sizeof(inzio);

	param[7].buffer_type = MYSQL_TYPE_TIME;
	param[7].buffer = (char *)&fine;
	param[7].buffer_length = sizeof(fine);

	param[8].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[8].buffer = codice_proposta;
	param[8].buffer_length = strlen(codice_proposta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add appointment\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve add appointment\n");
	}else{
		printf("Appointment correctly added...\n");
	}

	mysql_stmt_close(prepared_stmt);


}

static void view_new_appointments(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	if(!setup_prepared_stmt(&prepared_stmt, "call nuovi_appuntamenti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize appointments list statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = conf.username;
	param[0].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for appointments list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve appointments list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of appointments assigned to you");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


}

static void view_all_appointments(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	if(!setup_prepared_stmt(&prepared_stmt, "call tutti_appuntamenti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize appointments list statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = conf.username;
	param[0].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for appointments list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve appointments list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of appointments assigned to you");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


}

static void delete_note(MYSQL *conn, char cf[17]){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];

//	char cf[17];
	char anno[5];
	char mese[3];
	char giorno[3];
	char ora[3];
	char minuti[3];
	MYSQL_TIME data;
	memset(&data,0, sizeof(data));

//	printf("\nCodice fiscale: ");
//	getInput(17, cf, false);
	printf("Data and hour: ");
	printf("\nDay: ");
	getInput(3, giorno, false);
	printf("Month: ");
	getInput(3, mese, false);
	printf("Year: ");
	getInput(5, anno, false);
	printf("Hour: ");
	getInput(3, ora, false);
	printf("Minutes: ");
	getInput(3, minuti, false);

	data.day=atoi(giorno);
	data.month=atoi(mese);
	data.year=atoi(anno);
	data.hour=atoi(ora);
	data.minute=atoi(minuti);



	if(!setup_prepared_stmt(&prepared_stmt, "call elimina_nota(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize delete note statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = (char*)&data;
	param[1].buffer_length = sizeof(data);


	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = conf.username;
	param[2].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for delete note\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not delete note\n");
	}else{
		printf("Note delete correctly...\n");
	}

	mysql_stmt_close(prepared_stmt);


}

static void view_active_proposals(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;

	if(!setup_prepared_stmt(&prepared_stmt, "call proposte_attive()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize active proposals list statement\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve active proposals list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nActive proposals list");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


}

static void edit_note(MYSQL *conn, char cf[17]){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];

//	char cf[17];
	char nota[129];
	char anno[5];
	char mese[3];
	char giorno[3];
	char ora[3];
	char minuti[3];
	MYSQL_TIME data;
	memset(&data,0, sizeof(data));
	
	

//	printf("\nCodice fiscale: ");
//	getInput(17, cf, false);
	printf("Data and hour: ");
	printf("\nDay: ");
	getInput(3, giorno, false);
	printf("Month: ");
	getInput(3, mese, false);
	printf("Year: ");
	getInput(5, anno, false);
	printf("Hour: ");
	getInput(3, ora, false);
	printf("Minutes: ");
	getInput(3, minuti, false);
	printf("Note: ");
	getInput(129, nota, false);

	data.day=atoi(giorno);
	data.month=atoi(mese);
	data.year=atoi(anno);
	data.hour=atoi(ora);
	data.minute=atoi(minuti);
	

	if(!setup_prepared_stmt(&prepared_stmt, "call modifica_nota(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize edit note statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_DATETIME;
	param[1].buffer = (char*)&data;
	param[1].buffer_length = sizeof(data);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = nota;
	param[2].buffer_length = strlen(nota);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = conf.username;
	param[3].buffer_length = strlen(conf.username);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for edit note\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not edit note\n");
	}else{
		printf("Change made...\n");
	}

	mysql_stmt_close(prepared_stmt);



}

static void add_note(MYSQL *conn, char cf[17]){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];

//	char cf[17];
	char nota[129];

//	printf("\nCodice fiscale: ");
//	getInput(17, cf, false);
	printf("Note: ");
	getInput(129, nota, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_nota(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize add note statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nota;
	param[1].buffer_length = strlen(nota);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = conf.username;
	param[2].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add note\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not add note\n");
	}else{
		printf("Note correctly added..\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void view_meeting_room(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	char citta[45];

	printf("\nCity: ");
	getInput(45, citta, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_sale(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize meeting rooms list statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = citta;
	param[0].buffer_length = strlen(citta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for meeting rooms list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve meeting rooms list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of busy meeting rooms in selected city");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}

static void new_accepted_proposal(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];

	char codice[11];
	char cf[17];

	printf("\nProposal ID: ");
	getInput(11, codice, false);
	printf("\nTax code: ");
	getInput(17, cf, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_proposta_accettata(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insert proposal statement\n", false);
	}
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = codice;
	param[0].buffer_length = strlen(codice);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = cf;
	param[1].buffer_length = strlen(cf);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = conf.username;
	param[2].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for insert proposal\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not insert new proposal\n");
	}else{
		printf("New proposal added correctly...\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void view_customers_list(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_lista_clienti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize customers list statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = conf.username;
	param[0].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for customers list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve customers list\n");
	}


	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of customers assigned to you");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
}

static void notes_managment(MYSQL *conn){
	
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char options[4] = {'1','2', '3', '4'};
	char op;	

	char cf[17];



		
	printf("\033[2J\033[H");
	printf("*** What should I do for you? ***\n\n");


	printf("\nCustomer tax code: ");
	getInput(17, cf, false);
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_note(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize meeting room list statement\n", false);
	}
	memset(param, 0, sizeof(param));
		
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = conf.username;
	param[1].buffer_length = strlen(conf.username);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for customers list\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve customers list\n");
		if(strcmp(mysql_stmt_sqlstate(prepared_stmt), "45002")==0){
			goto next;
		}
		getchar();
		return;
	}
next:
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of notes");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


	printf("\n\n1) Insert a note\n");
	printf("2) Edit a note\n");
	printf("3) Delete a note\n");
	printf("4) Return to main menu\n");

	op = multiChoice("Select an option", options, 4);

	switch(op) {
		case '1':
			add_note(conn, cf);
			break;
			
		case '2':
			edit_note(conn, cf);
			break;

		case '3':
			delete_note(conn, cf);
			break;

		case '4':
			return;

		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}
	getchar();
	return;
}

static void view_appointments(MYSQL *conn){
	char options[3] = {'1','2', '3'};
	char op;	

	printf("\033[2J\033[H");
	printf("*** What should I do for you? ***\n\n");
	printf("\n\n1) View new appointments\n");
	printf("2) View all appointments\n");
	printf("3) Return to main menu\n");

	op = multiChoice("Select an option", options, 3);

	switch(op) {
		case '1':
			view_new_appointments(conn);
			break;
			
		case '2':
			view_all_appointments(conn);
			break;

		case '3':
			break;

		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}
	return;
}

void run_as_officer(MYSQL *conn)
{
	char options[8] = {'1','2', '3', '4', '5', '6', '7', '8'};
	char op;
	
	printf("Switching to officer role...\n");

	if(!parse_config("users/funzionario.json", &conf)) {
		fprintf(stderr, "Unable to load officer configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) View customers list\n");
		printf("2) View selected customer\n");
		printf("3) View active proposals\n");
		printf("4) Insert new accepted proposal\n");
		printf("5) Manage notes (Insert/Edit/Delete)\n");
		printf("6) Add appointment\n");
		printf("7) View appointments\n");
		printf("8) Quit\n");

		op = multiChoice("Select an option", options, 8);

		switch(op) {
			case '1':
				view_customers_list(conn);
				break;
			
			case '2':
				view_customer(conn);
				break;

			case '3':
				view_active_proposals(conn);
				break;

			case '4':
				new_accepted_proposal(conn);
				break;

			case '5':
				notes_managment(conn);
				continue;
				
			case '6':
				view_meeting_room(conn);
				add_appointment(conn);
				break;

			case '7':
				view_appointments(conn);
				break;

			case '8':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
