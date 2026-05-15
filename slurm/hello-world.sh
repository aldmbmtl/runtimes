#!/bin/bash
#SBATCH --job-name=hello-slinky
#SBATCH --output=hello_%j.out
#SBATCH --error=hello_%j.err
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks=1

echo "Hello from Slurm!"
echo "Job ID: $SLURM_JOB_ID"
echo "Node: $(hostname)"
echo "Running on: $(date)"
sleep 10
echo "Job complete!"
