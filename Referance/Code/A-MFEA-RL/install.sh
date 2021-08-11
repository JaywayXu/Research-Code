# Import conda environment
conda env create -f amfearl.yml
conda activate amfearl

# Clone and install Metaworld
git clone https://github.com/rlworkgroup/metaworld
cd metaworld
pip install -e .
