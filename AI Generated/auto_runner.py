import os
import sys
import subprocess

def main():
    print("[AI Runner] Compiling Pthread Solution...")
    
    source_file = "solution.c"
    exe_file = "cramer_ai_threads"
    
    # Notice the inclusion of -lpthread and -lm
    compile_cmd = ["gcc", source_file, "-o", exe_file, "-lpthread", "-lm"]
    
    try:
        subprocess.run(compile_cmd, check=True)
        print(f"[AI Runner] Compilation successful: {exe_file}")
    except subprocess.CalledProcessError:
        print("[Error] Compilation failed.")
        sys.exit(1)
        
    print("[AI Runner] Launching Executable (N=1000)...")
    print("="*60)
    
    try:
        # Defaults to N=1000 to satisfy the problem constraints
        subprocess.run([f"./{exe_file}", "1000"], check=True)
    except KeyboardInterrupt:
        print("\n[AI Runner] Terminated by user.")
    except Exception as e:
        print(f"[Error] Execution failed: {e}")
        
    print("="*60)
    print("[AI Runner] Complete. Check ai_execution_log.txt for detailed thread logs.")

if __name__ == "__main__":
    main()