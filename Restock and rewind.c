#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define products 100               // upto 100 products
#define customers 100              // upto 100 customers
#define name_length 50              // lenght upto 50 char
#define product_name_length 50      // lenght upto 50 char
#define month_length 10              // lenght upto 10 char

struct product {
    char name[product_name_length];
    int quantity;
    float price;
};
struct customer {
    char name[name_length];
    int id;
    int total_products;
    struct product p[products];
    float total_amount;
};
struct monthlydata{
    char month[month_length];
    struct customer c[customers];
    int customers_count;
};
////functions declaration part ///
void add_customer(struct monthlydata *m);
void display_customer(struct monthlydata *m );
void save_data(struct monthlydata *m ,char *filename);
void most_purchased_product(struct monthlydata *m);
void display_existing_data(char *filename);
void compare_most_purchased_product(const char *month1, const char *month2, const char *customer_name);

//main function 
int main(){

   struct monthlydata m;
   m.customers_count = 0;

     printf("ENTER THE MONTH NAME :: \n\n");

     scanf("%s",m.month);

  int select;

  char filename[20];
  sprintf(filename, "%s.txt", m.month);


   while(1){
     printf("\t\t\t====RED MART MENU====\n");
     printf("\n1. Add Customer\n");
     printf("2. Display Customer Details\n");
     printf("3.Save The Monthly Data\n");
     printf("4.Mostly Purchased product by customers in a month\n");
     printf("5.Display existing details of %s\n ",m.month);
     printf("6.Most purchased products by customer \n");
     printf("7.Exit\n\n\n");

     printf(" ENTER THE NUMBER FOR NEXT ACTION ::");
     scanf("%d", &select);

     switch(select){
       case 1: 

         add_customer(&m);
         break;
       case 2:
         display_customer(&m );
         break;
       case 3:
         save_data(&m ,filename);
         break;
       case 4:
         most_purchased_product(&m);
         break;
       case 5:
         display_existing_data(filename);
         break;
       case 6:
       {
           char month1[month_length], month2[month_length], customer_name[name_length];
           printf("Enter the first month: ");
           scanf("%s", month1);
           printf("Enter the second month: ");
           scanf("%s", month2);
           printf("Enter customer name: ");
           scanf("%s", customer_name);

           compare_most_purchased_product(month1, month2, customer_name);
           break;
       }
       case 7:
          printf("\n\nTHANK YOU FOR USING RED MART ,NOW PROGRAM WILL EXITING\n\n");
          break;
       default:
        printf("ENTER A VALID OPTION TO CONTINUE ");     
     }
}

  return 0;

}


/// ading a customer function 

void add_customer(struct monthlydata *m){

  struct customer new;
  printf("Enter customer name: ");
  scanf("%s", new.name);
  printf("Enter customer id: ");
  scanf("%d", &new.id);
  printf("Enter total products purchased: ");
  scanf("%d", &new.total_products);

  // iteration to get product details
  for(int i=0;i < new.total_products;i++){

    printf("Product %d Name :",i+1); 
    scanf(" %s",new.p[i].name);
    printf("Product %d Price :",i+1);
    scanf(" %f",&new.p[i].price);
    new.total_amount += new.p[i].price;

  for(int j=0;j<m->customers_count;j++){
    for(int k=0;k<m->c[j].total_products;k++){
      if(strcmp(m->c[i].p[k].name ,new.p[i].name)==0){
        m->c[i].p[k].quantity++;
      }
    }
  }  
  }
  m->c[m->customers_count] = new;
  (m->customers_count)++;

  printf("Customer added successfully.\n\n\n");
  // Customer added successfully
}


// to display custome details
void display_customer(struct monthlydata *m ){
   if(m->customers_count == 0){
    printf("No customers found.\n");
    return;
  }
    printf( "Customer Details of %s:\n",m->month);
    for(int i=0;i < m->customers_count;i++){
      printf("Customer Name: %s\n",m->c[i].name);
      printf("Customer ID: %d\n",m->c[i].id);
      printf("Total Products Purchased: %d\n",m->c[i].total_products);
      for(int j=0;j<m->c[i].total_products;j++){
        printf("Product Name %d :%s - $%.2f \n",j+1,m->c[i].p[j].name,m->c[i].p[i].price);
      }
      printf("Total Amount Spent: %.2f\n",m->c[i].total_amount);
    }
  }


//Most purchased product 

void most_purchased_product(struct monthlydata *m){

  struct product most_purchased ={ "",0,0.0};

  for(int i=0;i <  m->customers_count;i++){
    for(int j=0;j < m->c[i].total_products;j++){
      if(m->c[i].p[j].quantity > most_purchased.quantity){

        most_purchased = m->c[i].p[j];
      }
    }
  }
  if(most_purchased.quantity >0){
    printf("Most purchased product in %s : %s \n\n\n", m->month ,most_purchased.name);
  }//in the month most purschased product will dipslay
  else{
    printf("No products purchased in %s.\n\n\n",m->month);
  } 
}


// to save the data to a file 
void save_data(struct monthlydata *m ,char *filename){
    FILE *fp;
  fp = fopen(filename,"w");
  if(fp == NULL){
    printf("Error opening file.\n");
    return;
  }

  fprintf(fp, "Monthly Data of %s:\n",m->month);{
    for(int i=0;i < m->customers_count;i++){
      fprintf(fp,"Customer Name ::%s\n",m->c[i].name);
      fprintf(fp,"Customer ID ::%d\n",m->c[i].id);
      fprintf(fp,"Total Products Purchased ::%d\n",m->c[i].total_products);
      fprintf(fp,"Products purchased::\n");
      for(int j=0;j < m->c[i].total_products;j++){

        fprintf(fp,"Product %d Name ::%s =$%.2f\n",j+1,m->c[i].p[j].name,m->c[i].p[j].price);
      }
      fprintf(fp,"Total Amount Spent ::%.2f\n",m->c[i].total_amount);
  }
     fclose(fp);
  }
  printf("Data saved to file successfully.\n");
}
void display_existing_data(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100];  
    printf("\nExisting Data:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    printf("\n");
}
void compare_most_purchased_product(const char *month1, const char *month2, const char *customer_name) {
    FILE *fp1, *fp2;
    struct monthlydata m1, m2;

    char filename1[20], filename2[20];
    sprintf(filename1, "%s.txt", month1);
    sprintf(filename2, "%s.txt", month2);

    // Read data from the first month's file
    fp1 = fopen(filename1, "r");
    if (fp1 == NULL) {
        perror("Error opening file 1");
        exit(EXIT_FAILURE);
    }

    fscanf(fp1, "%*s %s", m1.month);

    while (fgetc(fp1) != '\n');  // Skip to the next line

    for (int i = 0; i < customers; i++) {
        fscanf(fp1, "Customer Name ::%s", m1.c[i].name);
        if (strcmp(m1.c[i].name, customer_name) == 0) {

          //find similar customer
            fscanf(fp1, "Customer ID ::%d", &m1.c[i].id);
            fscanf(fp1, "Total Products Purchased ::%d", &m1.c[i].total_products);

            for (int j = 0; j < m1.c[i].total_products; j++) {
                fscanf(fp1, "Product %*d Name ::%s =$%f", m1.c[i].p[j].name, &m1.c[i].p[j].price);
            }

            fscanf(fp1, "Total Amount Spent ::%f", &m1.c[i].total_amount);
            break;
        }
    }

    fclose(fp1);

    // Read data from the second month's file
    fp2 = fopen(filename2, "r");
    if (fp2 == NULL) {
        perror("Error opening file 2");
        exit(EXIT_FAILURE);
    }

    fscanf(fp2, "%*s %s", m2.month);

    while (fgetc(fp2) != '\n');  // Skip to the next line

    for (int i = 0; i < customers; i++) {
        fscanf(fp2, "Customer Name ::%s", m2.c[i].name);
        if (strcmp(m2.c[i].name, customer_name) == 0) {
            // Found the customer, store relevant data
            fscanf(fp2, "Customer ID ::%d", &m2.c[i].id);
            fscanf(fp2, "Total Products Purchased ::%d", &m2.c[i].total_products);

            for (int j = 0; j < m2.c[i].total_products; j++) {
                fscanf(fp2, "Product %*d Name ::%s =$%f", m2.c[i].p[j].name, &m2.c[i].p[j].price);
            }

            fscanf(fp2, "Total Amount Spent ::%f", &m2.c[i].total_amount);
            break;
        }
    }

    fclose(fp2);

    // Compare the most purchased product
    if (m1.c[0].total_products > 0 && m2.c[0].total_products > 0) {
        int most_purchased_index1 = 0;
        int most_purchased_index2 = 0;

        for (int j = 1; j < m1.c[0].total_products; j++) {
            if (m1.c[0].p[j].quantity > m1.c[0].p[most_purchased_index1].quantity) {
                most_purchased_index1 = j;
            }
        }

        for (int j = 1; j < m2.c[0].total_products; j++) {
            if (m2.c[0].p[j].quantity > m2.c[0].p[most_purchased_index2].quantity) {
                most_purchased_index2 = j;
            }
        }

        printf("Most purchased product by %s in %s: %s\n", customer_name, month1, m1.c[0].p[most_purchased_index1].name);
        printf("Most purchased product by %s in %s: %s\n", customer_name, month2, m2.c[0].p[most_purchased_index2].name);
    } else {
        printf("No data available for the customer %s in one or both months.\n", customer_name);
    }
}
