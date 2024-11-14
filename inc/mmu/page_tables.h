#ifndef PAGE_TABLES_H__
#define PAGE_TABLES_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void apply_page_tables_el3(void);
void apply_page_tables_el2(void);
void apply_page_tables_el1(void);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // PAGE_TABLES_H__