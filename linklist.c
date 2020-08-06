#include <stdio.h>
#include <stdlib.h>

// 双方向リンクリスト型
struct Node {
  int value;
  struct Node* next;
  struct Node* prev;
};

// 末尾探し
struct Node* search_tail(struct Node* list) {
  struct Node* p = list;

  // p->next が NULL である場合末尾
  while (p->next != NULL) {
    p = p->next;
  } 
  return p;
}

// 要素探し
// 引数をオプショナルにしたい.引数がなかったら末尾を返すのような
struct Node* search_node(struct Node* list, int locate) {
  struct Node* p = list; 
  int i;

  for (i=0;i<locate;i++) {
    p = p->next;
  }

  return p;
}

// リスト生成
struct Node* create_list(void) {
  struct Node* head = malloc(sizeof(struct Node));
   
  head->value = 0;
  head->next = NULL;

  return head;
}

// 要素を末尾に挿入
void add_node(struct Node* node, int value) {
  // 末尾探索
  struct Node* tail = search_tail(node);

  // 挿入するノードを生成
  struct Node* new = malloc(sizeof(struct Node));
  new->value = value;
  new->next = NULL;
  new->prev = tail;

  // 位置がずれる
  tail->next = new;
   
}

// 指定した場所にノードを挿入
// 引数をオプショナルにしたい.引数がなかったら末尾に挿入するような
void insert_node(struct Node* list, int value, int locate) {
  // 挿入する場所を場所を決定したい
  struct Node* p = search_node(list,locate);
  struct Node* prev = p->prev;
   
  // 挿入するノードを生成 
  struct Node* new = malloc(sizeof(struct Node));
  new->value = value;
  new->next = p;
  new->prev = p->prev;

  // ずらした分をpに適応する
  p->prev = new;
  prev->next = new;
}

// リストのメモリを解放
void clear_list(struct Node* list) {
  struct Node* p = list->next;
  struct Node* preve = list;

  while (p != NULL) {
    preve->next = p->next;

    // メモリを解放する前にノードの連結を変更しておく
    free(p);

    p = preve->next;
  }
}

// リストを完全に削除
void delete_list(struct Node* list) {
   clear_list(list);

   free(list);
}

// 要素を標準出力する
void show_list(struct Node* list) {
  struct Node* node = list;

  while (node->next != NULL) {
    printf("%3d\n",node->value);
    node = node->next;
  }
  printf("%3d\n",node->value);  
}

int main(void) {
  struct Node* list0;

  list0 = create_list();
  add_node(list0,10);
  add_node(list0,20);
  add_node(list0,30);
  add_node(list0,40);
  insert_node(list0,50,1);
  show_list(list0);

  delete_list(list0);

  return 0;
}
