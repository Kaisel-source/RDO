/**
 * @file skills.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/
#ifndef SKILLS_H
#define SKILLS_H
#include "../common/common.h"
#include "../common/struct.h"

/**
 * @brief Structure of the skill
 * 
 * id : Id of the skill
 * name : Name of the skill
 * desc : Description of the skill
 * damage : Damage of the skill
 * mana : Mana cost of the skill
 * level_min : Level required to use the skill
*/
typedef struct skills_t{
    int id;
    char name[50];
    char desc[100];
    int damage;
    int mana;
    int level_min;
} skills_s;


/**
 * @brief Structure of the skill list
 * 
 * skill : Skill
 * next : Next skill
 * prev : Previous skill
*/
typedef struct skills_list_t{
    skills_s * skill;
    struct skills_list_t *next;
    struct skills_list_t *prev;
} skills_list_s;


/**
 * @brief Structure of the skill inventory
 * 
 * head : Head of the list
 * nb_skills : Number of skills in the list
*/
typedef struct skills_inventory_t{
    skills_list_s *head;
    int nb_skills;
} skills_inventory;

/**
 * @brief Create the skill
 * 
 * @param id Id for the skill
 * @param name Name of the skill
 * @param desc Description of the skill
 * @param damage Damage of the skill
 * @param mana Mana cost of the skill
 * @param level_min Level required to use the skill
 * @return skills_s* 
 */
skills_s *skills_create(int id, char *name, char *desc, int damage, int mana, int level_min);

/**
 * @brief Initialize the skills list
 * 
 * @return skills_inventory* 
 */
skills_inventory *skills_list_create();

/**
 * @brief Destroy the skill
 * 
 * @param skill Skill to destroy
 */
void skills_destroy(skills_s **skill);

/**
 * @brief Destroy the skills list
 * 
 * @param list List to destroy
 */
void skills_list_destroy(skills_inventory **list);

/**
 * @brief Add a skill to the list
 * 
 * @param list List to add the skill
 * @param skill Skill to add
 */
void skills_list_add(skills_inventory *list, skills_s *skill);

/**
 * @brief Display the skill
 * 
 * @param skill Skill to display
 */
int skills_use(skills_s *skill, perso* player); // return > 0 if success, 0 if fail

#endif