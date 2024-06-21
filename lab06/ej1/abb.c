#include "abb.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_abb {
    abb_elem elem;
    struct _s_abb* left;
    struct _s_abb* right;
};

static bool elem_eq(abb_elem a, abb_elem b) { return a == b; }

static bool elem_less(abb_elem a, abb_elem b) { return a < b; }

static abb_elem max(abb_elem a, abb_elem b) {
    if (elem_less(a, b)) {
        return b;
    } else {
        return a;
    }
}

static abb_elem min(abb_elem a, abb_elem b) {
    if (elem_less(a, b)) {
        return a;
    } else {
        return b;
    }
}

static abb_elem subtree_max(abb tree) {
    assert(tree != NULL);
    abb_elem max_e = tree->elem;
    if (tree->right != NULL) {
        max_e = max(max_e, subtree_max(tree->right));
    }
    if (tree->left != NULL) {
        max_e = max(max_e, subtree_max(tree->left));
    }
    return max_e;
}

static abb_elem subtree_min(abb tree) {
    assert(tree != NULL);
    abb_elem min_e = tree->elem;
    if (tree->right != NULL) {
        abb_elem opt = subtree_min(tree->right);
        min_e = min(min_e, opt);
    }
    if (tree->left != NULL) {
        min_e = min(min_e, subtree_min(tree->left));
    }

    return min_e;
}

static bool invrep(abb tree) {
    if (tree == NULL) {
        return true;
    }

    bool ok = invrep(tree->left) && invrep(tree->right);
    if (tree->left != NULL) {
        ok = ok && elem_less(subtree_max(tree->left), tree->elem);
    }
    if (tree->right != NULL) {
        ok = ok && elem_less(tree->elem, subtree_min(tree->right));
    }

    return ok;
}

abb abb_empty(void) {
    abb tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree == NULL) {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else if (elem_less(e, tree->elem)) {
        tree->left = abb_add(tree->left, e);
    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_add(tree->right, e);
    }

    assert(invrep(tree) && abb_exists(tree, e));

    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));

    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));

    bool exists =
        tree != NULL && (tree->elem == e || abb_exists(tree->left, e) ||
                         abb_exists(tree->right, e));

    assert(abb_length(tree) != 0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    assert(invrep(tree));

    unsigned length = 0;
    if (tree != NULL) {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree == NULL) {
    } else if (elem_eq(tree->elem, e)) {
        if (tree->left == NULL) {
            abb tmp = tree->right;
            free(tree);
            tree = tmp;
        } else if (tree->right == NULL) {
            abb tmp = tree->left;
            free(tree);
            tree = tmp;
        } else {
            abb_elem min_e = subtree_min(tree->right);
            tree->elem = min_e;
            tree->right = abb_remove(tree->right, min_e);
        }
    } else if (elem_less(e, tree->elem)) {
        tree->left = abb_remove(tree->left, e);
    } else {
        tree->right = abb_remove(tree->right, e);
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));

    abb_elem root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));

    abb_elem max_e = subtree_max(tree);

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));

    abb_elem min_e = subtree_min(tree);

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord == ABB_IN_ORDER || ord == ABB_PRE_ORDER ||
                            ord == ABB_POST_ORDER));

    if (tree == NULL) return;

    switch (ord) {
        case ABB_IN_ORDER:
            abb_dump(tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump(tree->right, ord);
            break;
        case ABB_PRE_ORDER:
            printf("%d ", tree->elem);
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            break;
        case ABB_POST_ORDER:
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            printf("%d ", tree->elem);
            break;
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (tree != NULL) {
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}
