from cryptography.hazmat.primitives.asymmetric import rsa


"""
生成质数作为pq
"""

# 生成两个1024位的质数
def generate_prime_pair(bit_length=2048):
    private_key1 = rsa.generate_private_key(public_exponent=65537, key_size=bit_length)
    private_key2 = rsa.generate_private_key(public_exponent=65537, key_size=bit_length)

    # 提取质数
    prime1 = private_key1.private_numbers().p
    prime2 = private_key2.private_numbers().p

    return prime1, prime2


prime1, prime2 = generate_prime_pair()
print(f"Prime 1: {prime1}")
print(f"Prime 2: {prime2}")
