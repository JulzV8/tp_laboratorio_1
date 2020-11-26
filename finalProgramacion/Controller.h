int controller_clientSaveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saleSaveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_loadId(char* path, int* bufferId);
int controller_searchClientById(LinkedList* pArrayListEmployee, int id, int* index);
int controller_searchClientByCuit(LinkedList* pArrayListEmployee, char* cuit);
int controller_searchSaleById(LinkedList* pArrayListEmployee, int id, int* index);
int controller_clientLoadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_saleLoadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_addClient(LinkedList* pArrayListEmployee);
int controller_addSale(LinkedList* pArrayListEmployee,LinkedList* pArrayListClientes);
int controller_editSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales);
int controller_cobrarSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales);
//int controller_removeEmployee(LinkedList* pArrayListEmployee);

//int controller_sortEmployee(LinkedList* pArrayListEmployee);

