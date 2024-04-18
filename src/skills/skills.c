#include "../../include/skills/skills.h"

skills_s *skills_create(int id, char *name, char *desc, int damage, int mana, int level_min){
    skills_s *skill = (skills_s *)malloc(sizeof(skills_s));
    skill->id = id;
    strcpy(skill->name, name);
    strcpy(skill->desc, desc);
    skill->damage = damage;
    skill->mana = mana;
    skill->level_min = level_min;
    return skill;

}
skills_inventory *skills_list_create(){
    skills_inventory *list = (skills_inventory *)malloc(sizeof(skills_inventory));
    list->head = NULL;
    list->nb_skills = 0;
    return list;
}

void skills_destroy(skills_s **skill){
    //free((*skill)->name);
    //free((*skill)->desc);
    free(*skill);
    *skill = NULL;
}

void skills_list_destroy(skills_inventory **list){
    skills_list_s *current = (*list)->head;
    skills_list_s *next;
    while(current != NULL){
        next = current->next;
        skills_destroy(&(current->skill));
        current->next = NULL;
        current->prev = NULL;
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}

void skills_list_add(skills_inventory *list, skills_s *skill){
    skills_list_s *new_skill = (skills_list_s *)malloc(sizeof(skills_list_s));
    new_skill->skill = skill;
    new_skill->next = list->head;
    new_skill->prev = NULL;
    if(list->head != NULL){
        list->head->prev = new_skill;
    }
    list->head = new_skill;
    list->nb_skills++;
}

int skills_use(skills_s *skill, perso* player){
    if(player->mp < skill->mana){
        return 0;
    }if(player->level < skill->level_min){
        return 0;
    }
    player->mp -= skill->mana;
    return skill->damage;
}

void skills_display(skills_s *skill){
    printf("Skill: %s\n", skill->name);
    printf("Description: %s\n", skill->desc);
    printf("Damage: %d\n", skill->damage);
    printf("Mana cost: %d\n", skill->mana);
    printf("Level required: %d\n", skill->level_min);
}