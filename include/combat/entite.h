#ifndef ENTITE_H
#define ENTITE_H

#include "../common/common.h"


/*
 * @brief Create a entity object
 * 
 * @param prenom 
 * @param classe 
 * @param pv 
 * @param pv_max 
 * @param attaque 
 * @param equipe 
 * @param mouv 
 * @param initiative 
 * @param range 
 * @return entite_t 
 */
entite_t create_entity(const char *prenom, const char *classe, int pv, int pv_max, int attaque, int equipe, int mouv, int initiative, int range);

/**
 * @brief met les stat a 0 et a NULL
 * 
 * @param entite 
 */
void initialiser_Entite(entite_t *entite);

#endif /* ENTITE_H */
