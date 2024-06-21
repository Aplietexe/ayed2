#include "dict.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "key_value.h"

static dict_t dict_min(dict_t dict);
static dict_t dict_max(dict_t dict);
static dict_t dict_remove_node(dict_t dict);
static bool invrep(dict_t d);

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    if (d == NULL) {
        return true;
    }

    bool ok = invrep(d->left) && invrep(d->right);
    if (d->left != NULL) {
        ok = ok && key_less(dict_max(d->left)->key, d->key);
    }
    if (d->right != NULL) {
        ok = ok && key_less(d->key, dict_min(d->right)->key);
    }

    return ok;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;

    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));

    if (dict == NULL) {
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    } else if (key_less(word, dict->key)) {
        dict->left = dict_add(dict->left, word, def);
    } else if (key_less(dict->key, word)) {
        dict->right = dict_add(dict->right, word, def);
    } else {
        value_destroy(dict->value);
        dict->value = def;
    }

    assert(invrep(dict) && value_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));

    if (dict == NULL) {
        return NULL;
    } else if (key_eq(word, dict->key)) {
        return dict->value;
    } else if (key_less(word, dict->key)) {
        return dict_search(dict->left, word);
    } else {
        return dict_search(dict->right, word);
    }
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));

    return dict_search(dict, word) != NULL;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));

    if (dict == NULL) {
        return 0;
    } else {
        return 1 + dict_length(dict->left) + dict_length(dict->right);
    }
}

static dict_t dict_min(dict_t dict) {
    assert(dict != NULL);

    if (dict->left == NULL) {
        return dict;
    } else {
        return dict_min(dict->left);
    }
}

static dict_t dict_max(dict_t dict) {
    assert(dict != NULL);

    if (dict->right == NULL) {
        return dict;
    } else {
        return dict_max(dict->right);
    }
}

static dict_t dict_remove_node(dict_t dict) {
    if (dict->left == NULL) {
        dict_t tmp = dict->right;
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);
        return tmp;
    } else if (dict->right == NULL) {
        dict_t tmp = dict->left;
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);
        return tmp;
    } else {
        dict_t min_node = dict_min(dict->right);
        key_destroy(dict->key);
        value_destroy(dict->value);
        dict->key = min_node->key;
        dict->value = min_node->value;
        dict->right = dict_remove(dict->right, min_node->key);
        return dict;
    }
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    if (dict == NULL) {
        return dict;
    } else if (key_eq(dict->key, word)) {
        dict = dict_remove_node(dict);
    } else if (key_less(word, dict->key)) {
        dict->left = dict_remove(dict->left, word);
    } else {
        dict->right = dict_remove(dict->right, word);
    }

    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));

    if (dict != NULL) {
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }

    assert(dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE* file) {
    assert(invrep(dict) && file != NULL);

    if (dict != NULL) {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));

    dict = dict_remove_all(dict);

    assert(dict == NULL);
    return dict;
}
