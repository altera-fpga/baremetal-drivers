
Build with:
```
cmake -B build
cmake --build build -v
```

Setup Simics:
```
simics_intelfpga_cli --deploy agilex5e-universal
```

Run on Simics with:
```
simics test.simics
```
