import subprocess

policies = ['LRU', 'Random', 'Tree-LRU']
output_files = {
    'LRU': 'ResultsLRU.txt',
    'Random': 'ResultsRandom.txt',
    'Tree-LRU': 'ResultsTree-LRU.txt'
}

def run_cache_with_policy(policy, output_file):
    command = ['./cache', policy]
    
    with open(output_file, 'w') as file:
        try:
            result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            file.write(result.stdout)
            file.write(result.stderr)
            print(f"Results for {policy} saved to {output_file}")
        except Exception as e:
            print(f"Error running command for {policy}: {e}")

for policy in policies:
    run_cache_with_policy(policy, output_files[policy])

print("All simulations completed.")
