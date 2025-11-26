//
// Created by Герман Багдасарян on 26.11.2025.
//

#include "execution.h"

#include <string.h>
#include <stdlib.h>


typedef struct FunCalls FunCalls;

const int START_ARRAY_SIZE = 8;

struct FunCalls {
    Array *funCalls;
    char *currentFunName;
};

Array exceptions;
int currentExecutionId = -1;

ExecutionNode *executionNode(Tree *treeNode, ExecutionNode *nextNode,
                             ExecutionNode *breakNode, FunCalls *funCalls);

char *mallocString(char *text) {
    char *pointer = malloc(sizeof(char) * 1024);
    sprintf(pointer, "%s", text);
    return pointer;
}

// добавление в массив с возможным динамическим расширением
void addToList(Array *currentArray, void *element) {
    void **nodes;
    if (currentArray->size != currentArray->nextPosition) {
        nodes = currentArray->elements;
    } else {
        nodes = malloc(sizeof(void *) * 2 * currentArray->size);
        for (int i = 0; i < currentArray->size; ++i) {
            nodes[i] = currentArray->elements[i];
        }
        free(currentArray->elements);
    }
    nodes[currentArray->nextPosition] = element;
    currentArray->nextPosition += 1;
}

void addException(char *text) {
    char *exception = mallocString(text);
    addToList(&exceptions, exception);
}

int getNextExecutionId() {
    currentExecutionId++;
    return currentExecutionId;
}

// утилита для получения всех node дерева разбора в виде массива (вызвано
// бинарной реализацией листов)
Array findListItemsUtil(Tree *treeNode) {
    Tree **nodes = malloc(sizeof(Tree *) * START_ARRAY_SIZE);
    Array items = {START_ARRAY_SIZE, 0, nodes};

    Tree *currentListNode = treeNode;
    do {
        if (currentListNode->child_count == 0) {
            currentListNode = NULL;
        } else if (currentListNode->child_count == 1) {
            addToList(&items, currentListNode->children[0]);
            currentListNode = NULL;
        } else if (currentListNode->child_count == 2) {
            addToList(&items, currentListNode->children[0]);
            currentListNode = currentListNode->children[1];
        } else {
            char exceptionText[1024];
            sprintf(exceptionText,
                    "Exception in list parsing more than two by element id %d",
                    currentListNode->id);
            addException(exceptionText);
            return items;
        }
    } while (currentListNode != NULL);
    return items;
}

// получение корневого элемента из результатов парсинга
Tree *findSourceNode(FilenameParseTree input) {
    return input.tree->tree;
}

// получение списка функций из корневого элемента
Array findSourceItems(const Tree *source) {
    if (source->child_count != 0) {
        Tree *sourceItemsList = source->children[0];
        return findListItemsUtil(sourceItemsList);
    } else {
        return (Array) {0, 0, NULL};
    }
}

ExecutionNode *initExecutionNode(char *text) {
    ExecutionNode *node = malloc(sizeof(ExecutionNode));
    node->id = getNextExecutionId();
    node->text = mallocString(text);
    node->definitely = NULL;
    node->conditionally = NULL;
    node->operationTree = NULL;
    node->printed = 0;
    return node;
}

Tree *mallocTreeNode(char *type, char *value, int nodeNumber) {
    Tree *node = malloc(sizeof(Tree));
    node->id = getNextExecutionId();
    if (type) {
        node->type = mallocString(type);
    } else {
        node->type = NULL;
    }
    if (value) {
        node->value = mallocString(value);
    } else {
        node->value = NULL;
    }
    node->children = malloc(sizeof(Tree *) * nodeNumber);
    node->child_count = nodeNumber;
    return node;
}

// создание блока listStatement
ExecutionNode *executionListStatementNode(Tree *treeNode,
                                          ExecutionNode *nextNode,
                                          ExecutionNode *breakNode,
                                          FunCalls *funCalls) {
    ExecutionNode *tmpNextNode = nextNode;
    if (treeNode->child_count == 2) {
        tmpNextNode = executionNode(treeNode->children[1], nextNode, breakNode, funCalls);
    }
    ExecutionNode *node = initExecutionNode("");
    node->definitely =
            executionNode(treeNode->children[0], tmpNextNode, breakNode, funCalls);
    return node;
}

ExecutionNode *executionVarNode(Tree *treeNode, ExecutionNode *nextNode,
                                ExecutionNode *breakNode) {
    ExecutionNode *node = initExecutionNode("");
    Array variablesList = {0, 0, NULL};
    Tree *typeNode = NULL;
    if (treeNode->child_count == 2) {
        typeNode = treeNode->children[1];
        variablesList = findListItemsUtil(treeNode->children[0]);
    } else {
        typeNode = treeNode->children[0];
    }
    char resultNodeType[1024];
    if (!strcmp(typeNode->type, "array")) {
        int size = 0;
        if (typeNode->child_count == 2) {
            size = findListItemsUtil(typeNode->children[1]).nextPosition;
        }
        sprintf(resultNodeType,
                "array of %s size %d",
                typeNode->value, size);
    } else {
        sprintf(resultNodeType, "%s", typeNode->value);
    }

    ExecutionNode *previous = node;
    for (int i = 0; i < variablesList.nextPosition; ++i) {
        char varNameAndType[1024];
        sprintf(varNameAndType,
                "%s as %s",
                ((Tree *) variablesList.elements[i])->value, resultNodeType);
        previous->definitely = initExecutionNode(varNameAndType);
        previous = previous->definitely;
    }
    previous->definitely = nextNode;
    return node;
}

//чтобы распарсить дерево операций в последовательность операций
/*ExecutionNode *executionExpressionNode(Tree *treeNode, ExecutionNode *nextNode, ExecutionNode *conditionallyNext,
                                       ExecutionNode *parentNode) {
    ExecutionNode *node = initExecutionNode("");
    int hasNewParent = 0;
    if (parentNode == NULL) {
        hasNewParent = 1;
        parentNode = initExecutionNode("");
    }
    node->definitely = nextNode;
    node->conditionally = conditionallyNext;
    if (treeNode->child_count == 2) {
        ExecutionNode *leftNode = executionExpressionNode(treeNode->children[0], NULL, NULL, parentNode);
        ExecutionNode *rightNode = executionExpressionNode(treeNode->children[1], node, NULL, leftNode);
    } else if (treeNode->child_count != 0 && !strcmp(treeNode->children[0]->type, "braces")) {
        executionExpressionNode(treeNode->children[0], node, NULL, parentNode);
    } else {
        parentNode->definitely = node;
    }
    if (hasNewParent) {
        return parentNode;
    } else {
        return node;
    }
}*/

// для построения дерева операций
Tree *operationTreeNode(Tree *parsingTree, FunCalls *funCalls) {
    Tree *node = NULL;

    if (!strcmp(parsingTree->type, "braces")) {
        return operationTreeNode(parsingTree->children[0], funCalls);
    } else if (!strcmp(parsingTree->type, "INCREMENT") || !strcmp(parsingTree->type, "DECREMENT")) {
        node = mallocTreeNode("SET", NULL, 2);
        char valuePlace[1024];
        sprintf(valuePlace,
                "value place '%s'",
                parsingTree->children[0]->value);
        node->children[0] = mallocTreeNode(NULL, valuePlace, 0);
        if (!strcmp(parsingTree->type, "INCREMENT")) {
            node->children[1] = mallocTreeNode("PLUS", NULL, 2);
        } else {
            node->children[1] = mallocTreeNode("MINUS", NULL, 2);
        }
        node->children[1]->children[0] = mallocTreeNode(NULL, "const: 1", 0);
        node->children[1]->children[1] = operationTreeNode(parsingTree->children[0], funCalls);
    } else if (!strcmp(parsingTree->type, "callOrIndexer")) {
        char executionName[1024];
        sprintf(executionName,
                "execute: %s",
                parsingTree->children[0]->value);
        if (parsingTree->child_count == 1) {
            node = mallocTreeNode(NULL, executionName, 0);
        } else {
            Array argsArray = findListItemsUtil(parsingTree->children[1]);
            node = mallocTreeNode(NULL, executionName, argsArray.nextPosition);
            for (int i = 0; i < argsArray.nextPosition; ++i) {
                node->children[i] = operationTreeNode(argsArray.elements[i], funCalls);
            }
        }
        char funCallOperationIdNodeString[1024];
        sprintf(funCallOperationIdNodeString, "%d", node->id);
        Tree *funCallOperationIdNode = mallocTreeNode("operationTreeId", funCallOperationIdNodeString, 1);
        Tree *calledFunNameNode = mallocTreeNode("call", parsingTree->children[0]->value, 0);
        funCallOperationIdNode->children[0] = calledFunNameNode;
        addToList(funCalls->funCalls, funCallOperationIdNode);
    } else if (parsingTree->child_count == 2) {
        node = mallocTreeNode(parsingTree->type, parsingTree->value, parsingTree->child_count);

        if (!strcmp(parsingTree->type, "SET")) {
            char valuePlace[1024];
            sprintf(valuePlace,
                    "value place '%s'",
                    parsingTree->children[0]->value);
            node->children[0] = mallocTreeNode(NULL, valuePlace, 0);
            node->children[1] = operationTreeNode(parsingTree->children[1], funCalls);
        } else {
            node->children[0] = operationTreeNode(parsingTree->children[0], funCalls);
            node->children[1] = operationTreeNode(parsingTree->children[1], funCalls);
        }
    } else if (parsingTree->child_count == 0) {
        if (!strcmp(parsingTree->type, "IDENTIFIER")) {
            node = mallocTreeNode("read", NULL, 1);
            char valuePlace[1024];
            sprintf(valuePlace,
                    "value place '%s'",
                    parsingTree->value);
            node->children[0] = mallocTreeNode(NULL, valuePlace, 0);
        } else {
            char constVal[1024];
            sprintf(constVal,
                    "const: %s",
                    parsingTree->value);
            node = mallocTreeNode(NULL, constVal, 0);
        }
    }
    return node;
}

char *expressionNodeToString(Tree *treeNode) {
    // TODO("делать доп действия и создавать доп узлы для каждого конкретного типа node")
    if (treeNode->child_count == 0) {
        return mallocString(treeNode->value);
    } else if (treeNode->child_count == 1) {
        char *childStr = expressionNodeToString(treeNode->children[0]);
        char text[1024];
        sprintf(text,
                "%s-%s-",
                treeNode->type, childStr);
        return mallocString(text);
    } else {
        char *childLeftStr = expressionNodeToString(treeNode->children[0]);
        char *childRightStr = expressionNodeToString(treeNode->children[1]);
        char text[1024];
        sprintf(text,
                "%s %s %s",
                childLeftStr, treeNode->type, childRightStr);
        return mallocString(text);
    }
}

ExecutionNode *executionExpressionNode(Tree *treeNode, FunCalls *funCalls) {
    ExecutionNode *node = initExecutionNode(expressionNodeToString(treeNode));
    node->operationTree = operationTreeNode(treeNode, funCalls);
    return node;
}

ExecutionNode *executionElseNode(Tree *treeNode, ExecutionNode *nextNode,
                                 ExecutionNode *breakNode, FunCalls *funCalls) {
    ExecutionNode *node = initExecutionNode("");
    if (treeNode->child_count == 1) {
        node->definitely = executionNode(treeNode->children[0],
                                         nextNode, breakNode, funCalls);
    } else {
        node->definitely = nextNode;
    }
    return node;
}

ExecutionNode *executionIfNode(Tree *treeNode, ExecutionNode *nextNode,
                               ExecutionNode *breakNode, FunCalls *funCalls) {
    ExecutionNode *node = initExecutionNode("");
    Tree *elseTreeNode = NULL;
    Tree *ifStatements = NULL;
    if (treeNode->child_count == 3) {
        //    случай когда есть стейтменты в if и существует else
        ifStatements = treeNode->children[1];
        elseTreeNode = treeNode->children[2];
    } else if (treeNode->child_count == 2 &&
               !strcmp(treeNode->children[1]->type, "else")) {
        //    когда нет стейтментов в if
        elseTreeNode = treeNode->children[1];
    } else if (treeNode->child_count == 2) {
        ifStatements = treeNode->children[1];
    }

    ExecutionNode *conditionNextNode = NULL;
    ExecutionNode *conditionConditionallyNode = NULL;
    if (elseTreeNode != NULL) {
        ExecutionNode *elseNode =
                executionElseNode(elseTreeNode, nextNode, breakNode, funCalls);
        conditionNextNode = elseNode;
    } else {
        conditionNextNode = nextNode;
    }
    if (ifStatements != NULL) {
        ExecutionNode *statementsNode =
                executionNode(ifStatements, nextNode, breakNode, funCalls);
        conditionConditionallyNode = statementsNode;
    }
    ExecutionNode *conditionNode = executionExpressionNode(treeNode->children[0], funCalls);
    node->definitely = conditionNode;
    conditionNode->definitely = conditionNextNode;
    conditionNode->conditionally = conditionConditionallyNode;
    return node;
}

ExecutionNode *executionWhileNode(Tree *treeNode, ExecutionNode *nextNode,
                                  ExecutionNode *breakNode, FunCalls *funCalls) {
    ExecutionNode *node = initExecutionNode("");
    ExecutionNode *statementNode = NULL;
    if (treeNode->child_count == 2) {
        statementNode = executionNode(treeNode->children[1], node, nextNode, funCalls);
    } else {
        statementNode = initExecutionNode("");
        statementNode->definitely = node;
    }
    ExecutionNode *conditionNode = executionExpressionNode(treeNode->children[0], funCalls);
    node->definitely = conditionNode;
    conditionNode->definitely = nextNode;
    conditionNode->conditionally = statementNode;
    return node;
}

ExecutionNode *executionDoNode(Tree *treeNode, ExecutionNode *nextNode,
                               ExecutionNode *breakNode, FunCalls *funCalls) {
    ExecutionNode *node = initExecutionNode("");
    Tree *conditionTreeNode = NULL;
    if (treeNode->child_count == 3) {
        conditionTreeNode = treeNode->children[2];
    } else {
        conditionTreeNode = treeNode->children[1];
    }
    ExecutionNode *doConditionNode = executionExpressionNode(conditionTreeNode, funCalls);
    doConditionNode->definitely = nextNode;
    doConditionNode->conditionally = node;
    ExecutionNode *statementNode = NULL;
    if (treeNode->child_count == 3) {
        statementNode = executionNode(treeNode->children[0], doConditionNode, nextNode, funCalls);
    } else {
        statementNode = initExecutionNode("");
        statementNode->definitely = doConditionNode;
    }
    node->definitely = statementNode;
    return node;
}

ExecutionNode *executionBreakNode(Tree *treeNode, ExecutionNode *nextNode,
                                  ExecutionNode *breakNode) {
    ExecutionNode *node = initExecutionNode("");
    if (breakNode == NULL) {
        char exceptionText[1024];
        sprintf(exceptionText,
                "Exception in BREAK tree node parsing id --> %d no loop for break found",
                treeNode[0].id);
        addException(exceptionText);
        ExecutionNode *exceptionNode = initExecutionNode(exceptionText);
        node->definitely = exceptionNode;
        exceptionNode->definitely = nextNode;
    } else {
        node->definitely = breakNode;
    }
    return node;
}

// созадние блока
ExecutionNode *executionNode(Tree *treeNode, ExecutionNode *nextNode,
                             ExecutionNode *breakNode, FunCalls *funCalls) {
    if (!strcmp(treeNode[0].type, "listStatement")) {
        return executionListStatementNode(treeNode, nextNode, breakNode, funCalls);
    } else if (!strcmp(treeNode[0].type, "var")) {
        return executionVarNode(treeNode, nextNode, breakNode);
    } else if (!strcmp(treeNode[0].type, "if")) {
        return executionIfNode(treeNode, nextNode, breakNode, funCalls);
    } else if (!strcmp(treeNode[0].type, "while")) {
        return executionWhileNode(treeNode, nextNode, breakNode, funCalls);
    } else if (!strcmp(treeNode[0].type, "break")) {
        return executionBreakNode(treeNode, nextNode, breakNode);
    } else if (!strcmp(treeNode[0].type, "do")) {
        return executionDoNode(treeNode, nextNode, breakNode, funCalls);
    } else {
//        expression
        ExecutionNode *expressionNode = executionExpressionNode(treeNode, funCalls);
        expressionNode->definitely = nextNode;
    }
}

ExecutionNode *initGraph(Tree *sourceItem, FunCalls *funCalls) {
    ExecutionNode *startNode = initExecutionNode("START");
    ExecutionNode *endNode = initExecutionNode("FINISH");
    Tree *funcDef = sourceItem->children[0];
    if (funcDef->child_count == 2) {
        ExecutionNode *listStatementNode =
                executionNode(funcDef->children[1], endNode, NULL, funCalls);
        startNode->definitely = listStatementNode;
    } else {
        startNode->definitely = endNode;
    }
    return startNode;
}

void initExceptions() {
    void **nodes = malloc(sizeof(char *) * START_ARRAY_SIZE);
    exceptions = (Array) {START_ARRAY_SIZE, 0, nodes};
}

Array *executionGraph(const FilenameParseTree *input, int size) {
    void **resultNodes = malloc(sizeof(FunExecution *) * START_ARRAY_SIZE);
    Array *result = malloc(sizeof(Array));
    result->size = START_ARRAY_SIZE;
    result->nextPosition = 0;
    result->elements = resultNodes;

    for (int i = 0; i < size; ++i) {
        initExceptions();
        const Tree *sourceNode = findSourceNode(input[i]);
        const Array sourceItems = findSourceItems(sourceNode);
        fprintf(stderr, "%i\n", sourceItems.size);
        for (int j = 0; j < sourceItems.nextPosition; ++j) {
            FunExecution *currentFunExecution = malloc(sizeof(FunExecution));
            if (!currentFunExecution) continue;

            Tree **currentSourceItemElements = (Tree **)sourceItems.elements;
            if (!currentSourceItemElements || !currentSourceItemElements[j]) {
                free(currentFunExecution);
                continue;
            }

            currentFunExecution->filename = input[i].filename;

            currentFunExecution->name =
                    currentSourceItemElements[j]->children[0]->children[0]->value;
            currentFunExecution->signature =
                    currentSourceItemElements[j]->children[0];
        fprintf(stderr, "%i\n", sourceItems.size);


            void **nodes = malloc(sizeof(Tree *) * START_ARRAY_SIZE);
            Array funs = (Array) {START_ARRAY_SIZE, 0, nodes};
            FunCalls funCalls = (FunCalls) {&funs, currentFunExecution->name};
            currentFunExecution->nodes = initGraph(currentSourceItemElements[j], &funCalls);
            Tree *funCallsRoot = mallocTreeNode("currentFunction", currentFunExecution->name,
                                                    funCalls.funCalls->nextPosition);
            for (int k = 0; k < funCalls.funCalls->nextPosition; ++k) {
                funCallsRoot->children[k] = funCalls.funCalls->elements[k];
            }
            currentFunExecution->funCalls = funCallsRoot;
            currentFunExecution->errorsCount = exceptions.nextPosition;
            currentFunExecution->errors = exceptions.elements;
            addToList(result, currentFunExecution);
        }
    }
    return result;
}

void printNode(Tree *node, FILE *outputFile) {
    if (node == NULL) {
        return;
    }
    int child_count = node->child_count;
    for (int i = 0; i < child_count; ++i) {
        printNode(node->children[i], outputFile);
        fprintf(outputFile, "node%d", node->id);
        fprintf(outputFile, "([");
        int typeExists = 0;
        if (node->type != NULL && strlen(node->type) > 0) {
            fprintf(outputFile, "Type: %s", node->type);
            typeExists = 1;
        }
        if (node->value != NULL && strlen(node->value) > 0) {
            if (typeExists) {
                fprintf(outputFile, ", ", node->value);
            }
            fprintf(outputFile, "Value: %s", node->value);
        }
        fprintf(outputFile, "])");

        Tree *childNode = node->children[i];
        fprintf(outputFile, " --> ");
        fprintf(outputFile, "node%d", childNode->id);
        fprintf(outputFile, "([");
        typeExists = 0;
        if (childNode->type != NULL && strlen(childNode->type) > 0) {
            fprintf(outputFile, "Type: %s", childNode->type);
            typeExists = 1;
        }
        if (childNode->value != NULL && strlen(childNode->value) > 0) {
            if (typeExists) {
                fprintf(outputFile, ", ");
            }
            fprintf(outputFile, "Value: %s", childNode->value);
        }
        fprintf(outputFile, "])");
        fprintf(outputFile, "\n");
    }
}

void printTreeNode(Tree *node, FILE *outputFile) {
    fprintf(outputFile, "flowchart TB\n");
    printNode(node, outputFile);
    fprintf(outputFile, "\n");
}

void printExecutionNode(ExecutionNode *father, ExecutionNode *child, FILE *outputFile, char *relationName) {
    fprintf(outputFile, "node%d", father->id);
    fprintf(outputFile, "([");
    fprintf(outputFile, "Text: %s", father->text);
    fprintf(outputFile, "])");
    fprintf(outputFile, " --%s--> ", relationName);
    fprintf(outputFile, "node%d", child->id);
    fprintf(outputFile, "([");
    fprintf(outputFile, "Text: %s", child->text);
    fprintf(outputFile, "])");
    fprintf(outputFile, "\n");
}

void printExecutionGraphNodeToFile(ExecutionNode *executionNode, FILE *outputOperationTreesFile,
                                   FILE *outputExecutionFile) {
    if (executionNode->printed) {
        return;
    } else {
        executionNode->printed = 1;
    }

    if (executionNode->operationTree) {
        char linkedExecutionNodeId[1024];
        sprintf(linkedExecutionNodeId, "%d", executionNode->id);
        Tree *linkedExecutionNode = mallocTreeNode("linked execution node id", linkedExecutionNodeId, 1);
        linkedExecutionNode->children[0] = executionNode->operationTree;
        printNode(linkedExecutionNode, outputOperationTreesFile);
    }

    ExecutionNode *definitely = executionNode->definitely;
    if (definitely) {
        printExecutionGraphNodeToFile(definitely, outputOperationTreesFile, outputExecutionFile);

        printExecutionNode(executionNode, definitely, outputExecutionFile, "definitely");
    }

    ExecutionNode *conditionally = executionNode->conditionally;
    if (conditionally) {
        printExecutionGraphNodeToFile(conditionally, outputOperationTreesFile, outputExecutionFile);

        printExecutionNode(executionNode, conditionally, outputExecutionFile, "conditionally");
    }
}

void printExecutionGraphToFile(ExecutionNode *executionNode, FILE *outputOperationTreesFile,
                               FILE *outputExecutionFile) {
    fprintf(outputOperationTreesFile, "flowchart TB\n");
    fprintf(outputExecutionFile, "flowchart TB\n");
    printExecutionGraphNodeToFile(executionNode, outputOperationTreesFile, outputExecutionFile);
    fprintf(outputOperationTreesFile, "\n");
    fprintf(outputExecutionFile, "\n");
}

void printExecution(FunExecution *funExecution, FILE *outputFunCallFile, FILE *outputOperationTreesFile,
                    FILE *outputExecutionFile) {
    printTreeNode(funExecution->funCalls, outputFunCallFile);
    printExecutionGraphToFile(funExecution->nodes, outputOperationTreesFile, outputExecutionFile);
}