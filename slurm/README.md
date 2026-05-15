# Slurm Job Examples

Example sbatch scripts for the Slinky Slurm cluster on Kubernetes.

## Usage

```bash
# Submit a hello-world job
sbatch hello-world.sh

# Submit a GPU test job (requires GPU nodes)
sbatch gpu-test.sh

# Check job status
squeue

# View job output
cat hello_*.out
cat gpu_*.out
```

## Fields for Slinky workload template

| Field | Value |
|-------|-------|
| git_url | https://github.com/aldmbmtl/runtimes.git |
| work_dir | slurm |
| build_command | chmod +x hello-world.sh gpu-test.sh |
| run_command | sbatch hello-world.sh |
