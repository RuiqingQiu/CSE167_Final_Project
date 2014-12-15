/*
 *  Terrain.h
 *  FinalProject
 *
 *
 */

class Terrain1 {
public:
    Terrain1( int size );
    ~Terrain1();
    
    void generate( int, float, float, float );
    
    float* getHeightMap();
    float getData( int, int );
    
    int getWidth();
    
private:
    float *heightMap;
    int width;
    float roughness;		// Roughness of generated height map ( more hills, mountains, etc )
    float k;				// smoothing constant
    
    void genTerrain( int, int, int, int, float );
    void smooth();
    
    float genDisp( float );
    
    void setData( int, int, float );
};