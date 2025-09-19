#include "stock_market.h"

Person* create_person(char *name, int id) {
    Person* new_person;
    new_person = (Person*)malloc(sizeof(Person));
    strcpy(new_person->name , name);
    new_person->id =id;
    return new_person;
}

Company* create_company(char *name, char *abbr, int order) {
    Company* new_comp;
    new_comp = (Company*)malloc((sizeof(Company)));
    strcpy(new_comp->name , name);
    strcpy(new_comp->stock_abbreviation , abbr);
    new_comp->market_order = order;
    return new_comp;
}

void add_company_to_market(StockMarket *market, Company *company) {
    market->company_count +=1;
    market->entries[(market->company_count)-1].company = company;
}

RequestNode* create_request_node(Person *p, int amount, float price) {
     RequestNode* new_req_node;
    new_req_node = (RequestNode*)malloc(sizeof(RequestNode));
    
    if (new_req_node == NULL) {
        return NULL;
    }

    new_req_node->data.person = (Person*)malloc(sizeof(Person));
    if (new_req_node->data.person == NULL) {
        free(new_req_node);
        return NULL;
    }
    
    strcpy(new_req_node->data.person->name , p->name);
    new_req_node->data.person->id = p->id;
    new_req_node->data.amount = amount;
    new_req_node->data.price_per_share = price;
    return new_req_node;
}

void insert_sorted(RequestNode **head, RequestNode *node, int ascending) {
    /* WRITE YOUR CODE HERE */
}

void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price) {
    int i, rest_of_buy;
    RequestNode *buy =NULL;
    RequestNode *sell =NULL;
    RequestNode *previous_sell;
    RequestNode *current_sell;
    RequestNode *new_buy;
    RequestNode *temp_head;
    Person *p;
    
    for(i=0; i<(market->company_count); ){
        if(strcmp(market->entries[i].company->stock_abbreviation, company_abbr) == 0){
            buy = market->entries[i].buy_requests;
            sell = market->entries[i].sell_requests;
            break;
        }
        i++;
    }
    
    if (i == market->company_count) {
    printf("Error: Company '%s' not found!\n", company_abbr);
    }
    
    for(i=0; i<people_count; i++){
        if(strcmp(people[i]->name, buyer_name) == 0){
            p = people[i];
            break;
        }
    }
    
    previous_sell = NULL;
    
    if (buy == NULL) {
    printf("1Company not found or buy/sell lists not initialized.\n");
    }
    
    current_sell = sell;
    
    if (current_sell == NULL) {
    printf("Sell request list is empty.\n");
    }
   
    


    if((current_sell->data.price_per_share) > price || current_sell==NULL){                              /*ilk price uymuyorsa direkt selle ekledim*/
        printf("4");
        RequestNode *current_buy;
        RequestNode *previous_buy;
        current_buy = buy;
        new_buy = create_request_node(p, amount, price);
        
        if(new_buy->data.price_per_share < current_buy->data.price_per_share){      /*sell listesinin baş nodeuna koyulacaksa*/
            new_buy->next = current_buy;
            market->entries[i].buy_requests = new_buy;
            printf("5");
        }
        else{                                                               /*sell listesinin ara noduna koyulacaksa*/
            previous_buy = current_buy;
            current_buy = current_buy->next;
            printf("6");
            while(new_buy->data.price_per_share > current_buy->data.price_per_share){
                previous_buy = current_buy;
                current_buy = current_buy->next;
            }
            previous_buy->next = new_buy;
            new_buy->next = current_buy;
            printf("7");
            }
            
    }
    
    else{                                                                       /*kesin buy olacak*/
        printf("8");
        if(current_sell->data.amount > amount){                                  /*ilk buy fazlaca yeterli geliyorsa*/
            current_sell->data.amount -= amount;
            printf("Trade executed: %d shares of %s at %f between %s, %s", amount, company_abbr, price, current_sell->data.person->name, buyer_name);
        }
        
        else if(current_sell->data.amount == amount){                             /*ilk buy tamı tamına yetiyorsa*//*headi çıkaracağım*/
                temp_head = current_sell;
                current_sell = current_sell->next;
                free(temp_head);
                printf("Trade executed: %d shares of %s at %f between %s, %s", amount, company_abbr, price, current_sell->data.person->name, buyer_name);
        }
        
        else if(current_sell->data.amount < amount){                             /*ilk buy yetmiyorsa kalanla tekrar buy*/
            temp_head = current_sell;
            current_sell = current_sell->next;
            free(temp_head);
            printf("Trade executed: %d shares of %s at %f between %s, %s", current_sell->data.amount, company_abbr, price, current_sell->data.person->name, buyer_name);
            insert_sell_request(market, people, people_count, buyer_name, company_abbr, amount-(current_sell->data.amount), price);
        }
    }
}

void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price) {
    int i, rest_of_sell;
    RequestNode *buy =NULL;
    RequestNode *sell =NULL;
    RequestNode *previous_buy;
    RequestNode *current_buy;
    RequestNode *new_sell;
    RequestNode *temp_head;
    Person *p;
    
    for(i=0; i<(market->company_count); ){
        if(strcmp(market->entries[i].company->stock_abbreviation, company_abbr) == 0){
            buy = market->entries[i].buy_requests;
            sell = market->entries[i].sell_requests;
            break;
        }
        i++;
    }
    
    if (i == market->company_count) {
    printf("Error: Company '%s' not found!\n", company_abbr);
    }
    
    for(i=0; i<people_count; i++){
        if(strcmp(((*people)+i)->name, seller_name) == 0){
            p = people[i];
            break;
        }
    }
    
    previous_buy = NULL;
    
    if (sell == NULL) {
    printf("2Company not found or buy/sell lists not initialized.\n");
    }
    if (buy == NULL) {
    printf("3Company not found or buy/sell lists not initialized.\n");
    }
    
    current_buy = buy;
    
    if (current_buy == NULL) {
        printf("Buy request list is empty.\n");
    }
    
    printf("2");
    printf("%f\n", buy->data.price_per_share);
    printf("3");


    if((current_buy->data.price_per_share) < price || current_buy==NULL){                              /*ilk price uymuyorsa direkt selle ekledim*/
        printf("4");
        RequestNode *current_sell;
        RequestNode *previous_sell;
        current_sell = sell;
        new_sell = create_request_node(p, amount, price);
        
        if(new_sell->data.price_per_share < current_sell->data.price_per_share){      /*sell listesinin baş nodeuna koyulacaksa*/
            new_sell->next = current_sell;
            market->entries[i].sell_requests = new_sell;
            printf("5");
        }
        else{                                                               /*sell listesinin ara noduna koyulacaksa*/
            previous_sell = current_sell;
            current_sell = current_sell->next;
            printf("6");
            while(new_sell->data.price_per_share > current_sell->data.price_per_share){
                previous_sell = current_sell;
                current_sell = current_sell->next;
            }
            previous_sell->next = new_sell;
            new_sell->next = current_sell;
            printf("7");
            }
            
    }
    
    else{                                                                       /*kesin buy olacak*/
        printf("8");
        if(current_buy->data.amount > amount){                                  /*ilk buy fazlaca yeterli geliyorsa*/
            current_buy->data.amount -= amount;
            printf("Trade executed: %d shares of %s at %f between %s, %s", amount, company_abbr, price, seller_name, current_buy->data.person->name);
        }
        
        else if(current_buy->data.amount == amount){                             /*ilk buy tamı tamına yetiyorsa*//*headi çıkaracağım*/
                temp_head = current_buy;
                current_buy = current_buy->next;
                free(temp_head);
                printf("Trade executed: %d shares of %s at %f between %s, %s", amount, company_abbr, price, seller_name, current_buy->data.person->name);
        }
        
        else if(current_buy->data.amount < amount){                             /*ilk buy yetmiyorsa kalanla tekrar buy*/
            temp_head = current_buy;
            current_buy = current_buy->next;
            free(temp_head);
            printf("Trade executed: %d shares of %s at %f between %s, %s", current_buy->data.amount, company_abbr, price, seller_name, current_buy->data.person->name);
            insert_sell_request(market, people, people_count, seller_name, company_abbr, amount-(current_buy->data.amount), price);
        }
        
    }
}

void print_market(StockMarket *market) {
    /* WRITE YOUR CODE HERE */
}
