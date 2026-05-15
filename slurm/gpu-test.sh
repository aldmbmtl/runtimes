#!/bin/bash
#SBATCH --job-name=gpu-test
#SBATCH --output=gpu_%j.out
#SBATCH --error=gpu_%j.err
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --gres=gpu:1

echo "GPU test job"
nvidia-smi
echo "Done!"
