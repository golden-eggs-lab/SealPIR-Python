import seal
print('Seal imported...')

import sealpir
print('SealPIR imported...')


scheme_type_in 	= seal.scheme_type(1) 								# bfv
b 				= seal.EncryptionParameters(scheme_type_in)

print('b')

# PirParams struct
sealpir.PirParams.enable_symmetric = True
sealpir.PirParams.enable_batching = True;
sealpir.PirParams.enable_mswitching = True;
sealpir.PirParams.ele_num = 2;
sealpir.PirParams.ele_size = 4;
sealpir.PirParams.elements_per_plaintext = 6;
sealpir.PirParams.num_of_plaintexts = 8;
sealpir.PirParams.d = 2;
sealpir.PirParams.expansion_ratio = 5;
sealpir.PirParams.nvec = 3;
sealpir.PirParams.slot_count = 5;

# Params fxns

sealpir.gen_encryption_params()
sealpir.gen_pir_params()
sealpir.verify_encryption_params()

# Pir server/client classes...
sealpir.PIRClient()


