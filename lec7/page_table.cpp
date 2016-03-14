#include <cstdio>

void make_table(unsigned int va, unsigned int pa)
{
	unsigned int pde_idx = va >> 22;
	unsigned int PT = pde_idx - 0x300 + 0x1;

	unsigned int pde_ctx = (PT << 12) + 0x3;

	unsigned int pte_idx = (va >> 12) & 0x3ff;

	unsigned int pte_ctx = (pa & 0xfffff000) + 0x3;

	printf("va 0x%08x, pa 0x%08x\npde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", va, pa, pde_idx, pde_ctx, pte_idx, pte_ctx);
}

int main()
{
	make_table(0xcd82c07c, 0x0c20907c);
	return 0;
}
