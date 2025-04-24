
#include <stdio.h>

int main() {

    char estado_1, estado_2, codigo_1[4], codigo_2[4], cidade_1[50], cidade_2[50];
    int populacao_1, populacao_2, pontosturisticos_1, pontosturisticos_2;
    float area_1, area_2, pib_1, pib_2;
    
    float densidadePopulacional_1, densidadePopulacional_2, pibPercapto_1, pibPercapto_2;


    // Carta 1
    printf("\nDigite os dados da Carta 1:\n");

    printf("Estado (A-H): ");
    scanf(" %c", &estado_1); 

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade_1);

    printf("População: ");
    scanf("%d", &populacao_1);

    printf("Área (em km²): ");
    scanf("%f", &area_1);

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib_1);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosturisticos_1);

    // Carta 2
    printf("\nDigite os dados da Carta 2:\n");

    printf("Estado (A-H): ");
    scanf(" %c", &estado_2); 

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", cidade_2);

    printf("População: ");
    scanf("%d", &populacao_2);

    printf("Área (em km²): ");
    scanf("%f", &area_2);

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib_2);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosturisticos_2);

    sprintf(codigo_1, "%c01", estado_1);
    sprintf(codigo_2, "%c02", estado_2);

    densidadePopulacional_1 = (float) populacao_1 / area_1;
    densidadePopulacional_2 = (float) populacao_2 / area_2;

    pibPercapto_1 = (float) pib_1 / populacao_1;
    pibPercapto_2 = (float) pib_2 / populacao_2;

    printf("\nCarta 01:\n");
    printf("Estado: %c\n", estado_1);
    printf("Código: %s\n", codigo_1);
    printf("Nome da Cidade: %s\n", cidade_1);
    printf("População: %d\n", populacao_1);
    printf("Área: %.2f km²\n", area_1);
    printf("PIB: %.2f bilhões de reais\n", pib_1);
    printf("Número de Pontos Turísticos: %d\n", pontosturisticos_1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidadePopulacional_1);
    printf("PIB per Capita %.2f reais\n", pibPercapto_1);

    printf("\nCarta 02:\n");
    printf("Estado: %c\n", estado_2);
    printf("Código: %s\n", codigo_2);
    printf("Nome da Cidade: %s\n", cidade_2);
    printf("População: %d\n", populacao_2);
    printf("Área: %.2f km²\n", area_2);
    printf("PIB: %.2f bilhões de reais\n", pib_2);
    printf("Número de Pontos Turísticos: %d\n", pontosturisticos_2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidadePopulacional_2);
    printf("PIB per Capita %.2f reais\n", pibPercapto_2);

    return 0;
}
