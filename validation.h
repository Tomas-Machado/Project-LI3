#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

// Validation functions

/**
 * @brief Valida uma data no formato yyyy/mm/dd.
 * 
 *  * A função verifica:
 * - O formato geral da data (tamanho, posições das barras)
 * - Se ano, mês e dia são números
 * - Se os valores de mês e dia estão dentro dos limites permitidos
 * - Se a data não é mais recente que a data atual
 * 
 * @param date String contendo a data a ser validada.
 * @return true se a data for válida, false caso contrário.
 */
bool validate_date(const char *date);

/**
 * @brief Valida uma duração no formato hh:mm:ss.
 * 
 * A função verifica:
 * - O formato geral da duração (tamanho, posições dos dois pontos).
 * - Se horas, minutos e segundos são números.
 * - Se os valores estão dentro dos limites permitidos:
 *   - Horas: 0-99
 *   - Minutos: 0-59
 *   - Segundos: 0-59
 * 
 * @param duration String contendo a duração a ser validada.
 * @return true se a duração for válida, false caso contrário.
 */
bool validate_duration(const char *duration);

/**
 * @brief Valida um endereço de email.
 * 
 * A função verifica:
 * - A presença de exatamente um caractere '@'.
 * - A presença de pelo menos um '.' após o '@'.
 * - O formato do nome de user (apenas caracteres alfanuméricos).
 * - O formato do domínio (apenas letras minúsculas entre '@' e o último '.').
 * - O formato do TLD (apenas letras minúsculas, comprimento entre 2 e 3 caracteres).
 * 
 * @param email String contendo o email a ser validado.
 * @return true se o email for válido, false caso contrário.
 */
bool validate_email(const char *email);


/**
 * @brief Valida o tipo de assinatura de um user.
 * 
 * @param subscription_type String contendo o tipo de assinatura a ser validada.
 * @return true se o tipo de assinatura for "normal" ou "premium", false caso contrário.
 */
bool validate_subscription(const char *subscription_type);

#endif