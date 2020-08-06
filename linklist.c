/*
 * 双方向リンクリスト
 *
 * 主な関数 リスト作成　      -> create_list 引数にリストの長さを取る。 
 *          ノード挿入        -> insert_node 引数は挿入するリストと場所、value
 *          リストのvalue出力 -> show_list 引数は出力したいリスト
 *
 * 依存関数 リスト作成        -> create_list <- create_node, add_node <- search_tail
 *          ノード挿入        -> insert_node <- search_node, len_list
 *          リストのvalue出力 -> show_list
 *
 * 追加関数 指定位置のノードの削除      -> delete_node 
 *          指定位置のノードのvalue変更 -> change_value
 *          リスト関連のメモリ解放      -> delete_list
 *
 */


#include <stdio.h>
#include <stdlib.h>

// 双方向リンクリスト型
struct Node {
  int value;
  struct Node* next;
  struct Node* prev;
};

// リストの長さを求める（エラー処理のため)
int len_list(struct Node* list) {
  if (list->next == NULL)
    return 1;
  else
    return 1 + len_list(list->next);
}

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

  for (i=0;i<locate;i++) 
    p = p->next;

  return p;
}

// ノード生成
struct Node* create_node(void) {
  struct Node* head = malloc(sizeof(struct Node));
   
  head->value = 0;
  head->next = NULL;
  head->prev = NULL;

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

// リスト生成
struct Node* create_list(int n) { // 引数にリストに含むノードの数を取る
  int i;
  struct Node* first = create_node();

  for (i=1;i<n;i++) 
    add_node(first,0);
  
  return first;
}


// 指定した場所にノードを挿入
// 引数をオプショナルにしたい.引数がなかったら末尾に挿入するような
void insert_node(struct Node* list, int value, int locate) {
  // エラー処理
  int len = len_list(list);

  if (locate >= len) {
    printf("out of range\n");
    exit(1);
  }

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

// 指定した位置のノードのvalueを変更する
void change_value(struct Node* list, int value, int locate) {
  // エラー処理
  int len = len_list(list);

  if (locate >= len) {
    printf("out of range\n");
    exit(1);
  }

  struct Node* p = search_node(list,locate);

  // value を変更
  p->value = value;
}

// 指定した位置のノードを削除
void delete_node(struct Node* list, int locate) {
  // エラー処理
  int len = len_list(list);

  if (locate >= len) {
    printf("out of range\n");
    exit(1);
  }

  // 削除するノードを決定
  struct Node* p = search_node(list,locate);
  struct Node* prev = p->prev;
  struct Node* next = p->next;

  // ポインタを変更 prevかnextがNULLだとしたらノードとしての型を持っていない
  if (prev != NULL)
    prev->next = next;
  if (next != NULL)
    next->prev = prev;

  // 削除するノードのメモリ解放
  free(p);
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
  struct Node* list1;

  list0 = create_list(3);
  show_list(list0);
  putchar('\n');

  insert_node(list0,1,2);
  show_list(list0);
  putchar('\n');

  add_node(list0,3);
  show_list(list0);
  putchar('\n');

  change_value(list0,2,0);
  show_list(list0);
  putchar('\n');

  delete_node(list0,3);
  show_list(list0);
  putchar('\n');  

  delete_list(list0);

  return 0;
}
