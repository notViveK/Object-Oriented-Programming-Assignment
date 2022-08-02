//defining th required header file
//new data type to store the attributes that describes a student
struct student {
	int roll;
	char name[100];
	int score;
};
typedef struct student ss;

//declaring the file pointer globally to be used by any function
FILE *fp;

//function to add the record of a new student
void addStudent() {
	ss s;

	fp = fopen("Records.txt", "a+");	//basic file opening operation
	if (fp == NULL) {
		printf("File Not Opened ! Program Aborting");	//check of NULL pointer formnation
		exit(0);
	}
	char name[100];
	//FILE* fp1 = fp;
	printf("Enter the roll of the student --> ");
	scanf("%d", &s.roll);

	printf("Enter the name of the student --> ");
	scanf(" %[^\n]s", s.name);

	printf("Enter the score of the student --> ");
	scanf("%d", &s.score);

	fwrite(&s, sizeof(ss), 1, fp); //writing into the file
	fclose(fp);
}

//function to display the records of every students in c
void displayAll() {
	ss s;
	fp = fopen("Records.txt", "r");
	if (fp == NULL) {
		printf("File Not Opened ! Program Aborting");
		exit(0);
	}
	while (fread(&s, sizeof(ss), 1, fp)) {
		//printf("hello");
		if (s.roll != -1)
			printf("%d %s %d\n", s.roll, s.name, s.score);
	}
	fclose(fp);
}

//function to search a record
void search() {
	fp = fopen("Records.txt", "r");
	if (fp == NULL) {
		printf("File Not Opened ! Program Aborting");
		exit(0);
	}
	int roll;
	printf("Enter the roll Number of the desired student --> ");
	scanf("%d", &roll);

	ss s, s1;
	int flag = 0;
	while (fread(&s, sizeof(ss), 1, fp)) {
		if (s.roll == roll)
		{
			s1.roll = s.roll; strcpy(s1.name, s.name); s1.score = s.score;
			flag = 1;
			break;
		}
	}
	if (flag == 1) //record to be searched found
	{
		//display the details
		printf("Record Found ! \n");
		printf("Roll of the student --> %d\n", s1.roll);
		printf("Name of the student --> %s \n", s1.name);
		printf("Score of the student --> %d\n", s1.score);
	}
	else { //record not found
		printf("Sorry Record Not Found !");

	}
	fclose(fp); //closing the file
	return;
}

//function to Delete a record
void delete() {
	//function will implment physical deletion
	fp = fopen("Records.txt", "r");
	FILE* fp1 = fopen("dummy.txt", "w");
	if (fp1 == NULL || fp == NULL) {
		printf("File Not Opened ! Program Aborting");
		exit(0);
	}

	int roll;
	printf("Enter the roll number of the student you want to delete -> ");
	scanf("%d", &roll);

	ss s;
	int flag = 0;

	while (fread(&s, sizeof(ss), 1, fp)) {
		ss s1;

		if (s.roll == roll) {
			char c[1];
			printf("Record Found ! Are you sure you want to delete this record (y/n) ");
			scanf("%s", c);

			if (strcmp(c, "y") == 0 || strcmp(c, "Y") == 0) {
				//if yes then no requirement of writing the record
				flag = 1;
				printf("Record Found and deleted successfully !\n");
			}
			else {
				fwrite(&s, sizeof(ss), 1, fp1);
			}
		}
		else
			fwrite(&s, sizeof(ss), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);	// to make the file pointer tto the start of the file
	// altho fseek(fp, 0, SEEK_SET) / rewind(fp) can be used instead
	//fseek(fp, offset, SEEK_CURR) can be used

	ss s1;
	if (flag == 1) {
		fp = fopen("dummy.txt", "r");
		fp = fopen("Records.txt", "w");
		if (fp == NULL) {
			printf("File Not Opened ! Program Aborting");
			exit(0);
		}
		//printf("hello");
		while (fread(&s1, sizeof(ss), 1, fp1)) {
			//printf("%d", s1.roll);
			fwrite(&s1, sizeof(ss), 1, fp);
		}
		fclose(fp1);
		fclose(fp);
		remove("dummy.txt");
	}

	else  {
		printf("Record to be deleted not found");
	}
	return;
}

//function to edit a record
void edit() {
	int roll;
	printf("Enter the roll number of the student to be edited --> ");
	scanf("%d", &roll);

	fp = fopen("Records.txt", "r");
	FILE* fp1 = fopen("dummy.txt", "w");
	if (fp1 == NULL || fp == NULL) {
		printf("File Not Opened ! Program Aborting");
		exit(0);
	}

	ss s;
	int flag = 0;

	while (fread(&s, sizeof(ss), 1, fp)) {
		ss s1;

		if (s.roll == roll) { //roll to be edited found
			char c[1];
			printf("Record Found !");
			printf("Roll of the student ---> %d\n", s.roll);
			printf("Name of the student ---> %s\n", s.name);
			printf("Score of the student ---> %d\n", s.score);

			printf("Are you sure you want to edit this record (y/n) ");
			scanf("%s", c);

			if (strcmp(c, "y") == 0 || strcmp(c, "Y") == 0) {	//final check
				//if yes then no requirement of writing the record
				ss s1;
				s1.roll = s.roll;


				printf("Enter the new name ---> ");
				scanf(" %[^\n]s", s1.name);

				printf("Enter the new score ---> ");
				scanf("%d", &s1.score);

				flag = 1;
				fwrite(&s1, sizeof(ss), 1, fp1);
				printf("Record edited successfully !\n");
			}
			else {
				fwrite(&s, sizeof(ss), 1, fp1);
			}
		}
		else
			fwrite(&s, sizeof(ss), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);	// to make the file pointer tto the start of the file
	// altho fseek(fp, 0, SEEK_SET) / rewind(fp) can be used instead

	ss s1;
	if (flag == 1) {
		fp = fopen("dummy.txt", "r");
		fp = fopen("Records.txt", "w");
		if (fp == NULL) {
			printf("File Not Opened ! Program Aborting");
			exit(0);
		}
		//printf("hello");
		while (fread(&s1, sizeof(ss), 1, fp1)) {
			//printf("%d", s1.roll);
			fwrite(&s1, sizeof(ss), 1, fp);
		}
		fclose(fp1);
		fclose(fp);
		remove("dummy.txt");
	}

	else  {//record not found case
		printf("Record to be edited not found");
	}
	return;

}
