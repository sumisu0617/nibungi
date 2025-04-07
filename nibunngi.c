#include <stdio.h>
#include <stdlib.h>

struct ST_NUM{
    int i_num;
    struct ST_NUM* st_right;
    struct ST_NUM* st_left;
};
struct ST_NUM* st_input(struct ST_NUM* st_nums);
struct ST_NUM* st_add(int num);
struct ST_NUM* st_insert(int i_inputnum, struct ST_NUM* st_insertnum);
struct ST_NUM* st_search(int i_searchnum, struct ST_NUM* st_searchtree, int* i_size);
void vd_count(struct ST_NUM* st_sortnum, int* size);
void vd_traversal(struct ST_NUM* st_sortnum);
void vd_traversal_insert(struct ST_NUM* st_sortnum, struct ST_NUM* st_new, int* i_size);
struct ST_NUM* st_traversal_insert(int i_inputnum, struct ST_NUM* st_insertnum);
struct ST_NUM* st_search(int i_searchnum, struct ST_NUM* st_searchtree, int* i_size);
struct ST_NUM* st_traversal_input(int i_size, struct ST_NUM* st_new, struct ST_NUM* st_sortnum);

int main(void){
    struct ST_NUM* st_num = NULL;
    struct ST_NUM* st_resultnum = NULL;
    int i_inputnum;
    int i_size = 0;
    
    st_num = st_input(st_num);
    if(st_num == NULL){
        printf("なにも入力されませんでした\n");
    }
    else{
        printf("値の入力が完了しました\n");
        vd_traversal(st_num);
        printf("検索したい値を入力してください\n");
        scanf("%d\n", &i_inputnum);
        st_resultnum = st_search(i_inputnum, st_num, &i_size);
        if(st_resultnum == NULL){
            printf("値は見つかりませんでした\n");
        }
        else{
            printf("%dは%d番目に格納されています\n", st_resultnum->i_num, i_size);
        }
    }
    
    free(st_num);
    st_num = NULL;
    
    return 0;
}

/* 二分木に値を入力 */
struct ST_NUM* st_input(struct ST_NUM* st_num){
    int i_scan;
    while(1){
        printf("数値を入力してください(終了する場合‐の値を入力)\n");
        scanf("%d\n", &i_scan);
        /* 最初の値の追加 */
        if(st_num == NULL){
            if(i_scan >= 0){
                st_num = st_add(i_scan);
            }
            else{
                return NULL;
            }
        }
        else{
            if(i_scan >= 0){
                st_num = st_insert(i_scan, st_num);
            }
            else{
                break;
            }
        }
    }
    
    return st_num;
}

/* 新しく枝を追加する */
struct ST_NUM* st_add(int i_nums){
    struct ST_NUM* st_adds;
    st_adds = (struct ST_NUM*)malloc(sizeof(struct ST_NUM));
    
    st_adds->i_num = i_nums;
    st_adds->st_left = NULL;
    st_adds->st_right = NULL;
    return st_adds;
}

/* 値の場所を検索して値を入れる */
struct ST_NUM* st_insert(int i_inputnum, struct ST_NUM* st_insertnum){
    /* 値の場所に追加 */
    if(st_insertnum == NULL){
        return st_add(i_inputnum);
    }
    /* 小さいので、左の枝に移動 */
    else if(i_inputnum < st_insertnum->i_num){
        st_insertnum->st_left = st_insert(i_inputnum, st_insertnum->st_left);
    }
    /* 大きいので右の枝に移動 */
    else if(i_inputnum > st_insertnum->i_num){
        st_insertnum->st_right = st_insert(i_inputnum, st_insertnum->st_right);
    }
    else{
        /* else none */
    }
    /* 値の代入が終わったので、そのアドレスを返す */
    return st_insertnum;
}

struct ST_NUM* st_search(int i_searchnum, struct ST_NUM* st_searchtree, int* i_size){
    struct ST_NUM* st_resultnum;
    *i_size = *i_size + 1;
    /* 値が見つかったもしくは値がなかったためそのアドレスを返す */
    if(st_searchtree == NULL || st_searchtree->i_num == i_searchnum){
        st_resultnum = st_searchtree;
    }
    /* 値が小さいため左を探す */
    else if(i_searchnum < st_searchtree->i_num){
        st_resultnum = st_search(i_searchnum, st_searchtree->st_left, i_size);
    }
    else{
        st_resultnum = st_search(i_searchnum, st_searchtree->st_right, i_size);
    }
    /* 値が大きいため右を探す */
    return st_resultnum;
}

void vd_count(struct ST_NUM* st_sortnum, int* size){
    if(st_sortnum != NULL){
        vd_count(st_sortnum->st_left, size);
        *size = *size + 1;
        vd_count(st_sortnum->st_right, size);
    }
    return;
}

void vd_traversal(struct ST_NUM* st_sortnum){
    struct ST_NUM* st_new;
    int i_size = 0;
    int i_insert_size = 0;
    vd_count(st_sortnum, &i_size);
    st_new = (struct ST_NUM*)malloc(i_size * sizeof(struct ST_NUM));
    vd_traversal_insert(st_sortnum, st_new, &i_insert_size);
    st_sortnum = st_traversal_input(i_size, st_new, st_sortnum);
    st_new = NULL;
    return;
}

void vd_traversal_insert(struct ST_NUM* st_sortnum, struct ST_NUM* st_new, int* i_size){
    if(st_sortnum != NULL){
        vd_traversal_insert(st_sortnum->st_left, st_new, i_size);
        st_new[*i_size] = *st_sortnum;
        *i_size = *i_size + 1;
        vd_traversal_insert(st_sortnum->st_right, st_new, i_size);
    }
    return;
}

struct ST_NUM* st_traversal_input(int i_size, struct ST_NUM* st_new, struct ST_NUM* st_sortnum){
    int i;
    int j;
    int group;
    free(st_sortnum);
    st_sortnum = NULL;
    for (group = i_size / 2; group > 0; group /= 2) {
        for (i = group; i < i_size; i++) {
            for (j = i; j >= group; j -= group) {
                if(st_sortnum == NULL){
                    st_sortnum = st_add(st_new[j].i_num);
                }
                else{
                    st_sortnum = st_insert(st_new[j].i_num, st_sortnum);
                }
            }
        }
    }
    return st_sortnum;
}