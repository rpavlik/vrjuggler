/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2003 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile$
 * Date modified: $Date$
 * Version:       $Revision$
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _GADGET_ASCENSION_FLOCKOFBIRD_STANDALONE_H_
#define _GADGET_ASCENSION_FLOCKOFBIRD_STANDALONE_H_

#include <vpr/IO/Port/SerialPort.h>
#include <vpr/vprTypes.h>
#include <string>
#include <boost/tuple/tuple.hpp>

#define POSITION_RANGE 12.0f
#define ANGLE_RANGE   180.0f
#define MAX_SENSORS    128


enum BIRD_HEMI
{
   FRONT_HEM, AFT_HEM, UPPER_HEM, LOWER_HEM, LEFT_HEM, RIGHT_HEM
};
inline std::string getHemiString(BIRD_HEMI hemi)
{
   if(FRONT_HEM == hemi) return "Front";
   else if(AFT_HEM == hemi) return "Aft";
   else if(UPPER_HEM == hemi) return "Upper";
   else if(LOWER_HEM == hemi) return "Lower";
   else if(LEFT_HEM == hemi) return "Left";
   else if(RIGHT_HEM == hemi) return "Right";
   else return "Unknown";
}

enum BIRD_FILT
{
   AC_NARROW, AC_WIDE, DC_FILTER
};
inline std::string getFiltString(BIRD_FILT filt)
{
   if(AC_NARROW == filt) return "AC Narrow";
   else if(AC_WIDE == filt) return "AC Wide";
   else if(DC_FILTER == filt) return "DC Filter";
   else return "Unknown";
}

namespace Transmitter
{
   /** Type of transmitter */
   enum Type
   { Ert0 = 0, Ert1 = 1, Ert2 = 2, Ert3 = 3, Standard, None };

   inline std::string getTransmitterString(Type type)
   {
      if(Ert0 == type)
      { return "Ert 0"; }
      else if(Ert1 == type)
      { return "Ert 1"; }
      else if(Ert2 == type)
      { return "Ert 2"; }
      else if(Ert3 == type)
      { return "Ert 3"; }
      else if(Standard == type)
      { return "Standard"; }
      return "None";
   }

   inline bool isErt(const Type type)
   {
      return ((type == Ert0) || (type == Ert1) || (type == Ert2) | (type == Ert3));
   }
}

namespace Flock
{
   // ------ Flock exceptions ------ //
   /** Base exception for flock errors */
   class FlockException : public std::exception
   {
   public:
      FlockException(const std::string& msg) : mMsg(msg)
      {;}

      virtual ~FlockException() throw()
      {;}

      const std::string& getMessage() const
      { return mMsg; }

      virtual const char* what() throw()
      { return mMsg.c_str();  }

   private:
      std::string mMsg;
   };

   /** Thrown when there are errors with the connection */
   class ConnectionException : public FlockException
   {
   public:
      ConnectionException(const std::string& msg="Connection exception") : FlockException(msg)
      {;}
      virtual ~ConnectionException() throw()
      {;}
   };

   /** Thrown when there are timeouts reading or writing */
   class TimeoutException : public FlockException
   {
   public:
      TimeoutException(const std::string& msg="Time out exception") : FlockException(msg)
      {;}
      virtual ~TimeoutException() throw()
      {;}
   };

   /** Thrown when there is invalid data read from the flock*/
   class InvalidDataException : public FlockException
   {
   public:
      InvalidDataException(const std::string& msg="Time out exception") : FlockException(msg)
      {;}
      virtual ~InvalidDataException() throw()
      {;}
   };

   /** Thrown when there is invalid data read from the flock*/
   class CommandFailureException : public FlockException
   {
   public:
      CommandFailureException(const std::string& msg="Time out exception") : FlockException(msg)
      {;}
      virtual ~CommandFailureException() throw()
      {;}
   };
   // ---------------------------------------------------------------------------------- //

   namespace Command
   {
      const vpr::Uint8 Angles(0x57);
      const vpr::Uint8 ChangeValue(0x50);
      const vpr::Uint8 ExamineValue(0x4F);
      const vpr::Uint8 FbbReset(0x2F);
      const vpr::Uint8 Hemisphere(0x4C);
      const vpr::Uint8 Matrix(0x58);
      const vpr::Uint8 NextTransmitter(0x30);
      const vpr::Uint8 Point(0x42);
      const vpr::Uint8 Position(0x56);
      const vpr::Uint8 PositionAngles(0x59);
      const vpr::Uint8 PositionMatrix(0x5A);
      const vpr::Uint8 PositionQuaternion(0x5D);
      const vpr::Uint8 Quaternion(0x5C);
      const vpr::Uint8 ReportRate1(0x51);
      const vpr::Uint8 ReportRate2(0x52);
      const vpr::Uint8 ReportRate8(0x53);
      const vpr::Uint8 ReportRate32(0x54);
      const vpr::Uint8 ToFbbNormal(0xF0);
      const vpr::Uint8 ToFbbExpanded(0xE0);
      const vpr::Uint8 ToFbbSuperExpanded(0xA0);
      const vpr::Uint8 Run(0x46);
      const vpr::Uint8 Sleep(0x47);
      const vpr::Uint8 Stream(0x40);
      const vpr::Uint8 StreamStop(0x3F);
      const vpr::Uint8 Sync(0x41);
   };

   namespace Parameter
   {
      const vpr::Uint8 BirdStatus(0x0);
      const vpr::Uint8 SoftwareRevision(0x01);
      const vpr::Uint8 CrystalSpeed(0x2);
      const vpr::Uint8 PositionScaling(0x3);
      const vpr::Uint8 FilterStatus(0x4);
      const vpr::Uint8 BirdRateCount(0x6);
      const vpr::Uint8 BirdRate(0x7);
      const vpr::Uint8 BirdErrorCode(0xA);
      const vpr::Uint8 BirdSuddenChange(0xE);
      const vpr::Uint8 ModelIdentification(0xF);
      const vpr::Uint8 BirdExpandedErrorCode(0x10);
      const vpr::Uint8 AddressingMode(0x13);
      const vpr::Uint8 FbbAddress(0x15);
      const vpr::Uint8 Hemisphere(0x16);
      const vpr::Uint8 GroupMode(0x23);
      const vpr::Uint8 FlockSystemStatus(0x24);
      const vpr::Uint8 FbbAutoConfig(0x32);

   }

   // Masks for bird status return value
   namespace BirdStatus
   {
      const vpr::Uint16 MasterBit(1<<15);
      const vpr::Uint16 BirdInitBit(1<<14);
      const vpr::Uint16 ErrorBit(1<<13);
      const vpr::Uint16 RunningBit(1<<12);
      const vpr::Uint16 HostSyncBit(1<<11);
      const vpr::Uint16 AddressModeBit(1<<10);
      const vpr::Uint16 CrtSyncBit(1<<9);
      const vpr::Uint16 SyncModeBit(1<<8);
      const vpr::Uint16 FactoryTestBit(1<<7);
      const vpr::Uint16 XonXoffBit(1<<6);
      const vpr::Uint16 SleepBit(1<<5);
      //const vpr::Uint16 PositionMask(0
      const vpr::Uint16 PointModeBit(1<<0);

      inline bool isMaster(vpr::Uint16 status)
      { return (MasterBit & status); }
      inline bool isInititalized(vpr::Uint16 status)
      { return (BirdInitBit & status); }
      inline bool hasError(vpr::Uint16 status)
      { return (ErrorBit & status); }
      inline bool isRunning(vpr::Uint16 status)
      { return (RunningBit & status); }
      inline bool isSleeping(vpr::Uint16 status)
      { return (SleepBit & status); }
   }

   namespace SystemStatus
   {
      const vpr::Uint8 AccessibleBit(1<<7);
      const vpr::Uint8 RunningBit(1<<6);
      const vpr::Uint8 SensorBit(1<<5);
      const vpr::Uint8 ErtBit(1<<4);
      const vpr::Uint8 Ert3Bit(1<<3);
      const vpr::Uint8 Ert2Bit(1<<2);
      const vpr::Uint8 Ert1Bit(1<<1);
      const vpr::Uint8 TransmitterBit(1<<0);

      inline bool isAccessible(vpr::Uint8 bstatus)
      { return (AccessibleBit & bstatus); }

      /** Is the bird running.  Running --> power on, auto-configed and awake */
      inline bool isRunning(vpr::Uint8 bstatus)
      { return (RunningBit & bstatus); }

      /** Does the unit have a sensor? */
      inline bool hasSensor(vpr::Uint8 bstatus)
      { return (AccessibleBit & bstatus); }

      inline bool isErt(vpr::Uint8 bstatus)
      { return (ErtBit & bstatus); }

      inline bool hasStandardTransmitter(vpr::Uint8 bstatus)
      { return ((TransmitterBit & bstatus) && (!isErt(bstatus)) ); }

      inline bool hasTransmitter(vpr::Uint8 bstatus)
      { return (isErt(bstatus) || hasStandardTransmitter(bstatus)); }

      inline Transmitter::Type getTransmitterType(vpr::Uint8 bstatus)
      {
         Transmitter::Type type;

         if(!hasTransmitter(bstatus))
         { type = Transmitter::None; }
         else if(hasStandardTransmitter(bstatus))
         { type = Transmitter::Standard; }
         else
         {
            if (Ert1Bit & bstatus)
            { type = Transmitter::Ert1; }
            else if (Ert2Bit & bstatus)
            { type = Transmitter::Ert2; }
            else if (Ert3Bit & bstatus)
            { type = Transmitter::Ert3; }
            else if (TransmitterBit & bstatus)
            { type = Transmitter::Ert0; }
         }

         return type;
      }
   }

   namespace Output
   {
      /** Format specifiers.
      * Indexed for bird status results and happily also so if you
      * Add (Command::Postion-1) to the value you get the command value to
      * send to switch to that mode. :)
      */
      enum Format
      {
         Position = 0x1,
         Angle = 0x2,
         Matrix = 0x3,
         PositionAngle = 0x4,
         PositionMatrix = 0x5,
         Quaternion = 0x7,
         PositionQuaternion = 0x8
      };
      inline std::string getFormatString(Format format)
      {
         if(Position == format) return "Position";
         else if(Angle == format) return "Angle";
         else if(Matrix == format) return "Matrix";
         else if(PositionAngle == format) return "PositionAngle";
         else if(PositionMatrix == format) return "PositionMatrix";
         else if(Quaternion == format) return "Quaternion";
         else if(PositionQuaternion == format) return "PositionQuaternion";
         else return "Unknown format";
      }
   }

   /** Report rate for bird sampling */
   enum ReportRate
   {
      MaxRate = 0x51,          /**< Use maximum rate */
      EveryOther = 0x52,   /**< Every other sample */
      Every8 = 0x53,       /**< Every 8th sample */
      Every32 = 0x54       /**< Every 32nd sample */
   };
   inline std::string getReportRateString(ReportRate rate)
   {
      if(MaxRate == rate) return "MaxRate";
      else if(EveryOther == rate) return "EveryOther";
      else if(Every8 == rate) return "Every8";
      else if(Every32 == rate) return "Every32";
   }

   /** Mode the flock is executing in.
   * This is not specifically defined in the flock manual, but falls out of how you need to manage the system.
   */
   enum Mode
   {
      UnknownMode = 0,     /**< Default unknown mode */
      Standalone = 1,      /**< Mode with single unit with transmitter and bird */
      Standard = 2,        /**< Mode with only a single standard transmitter */
      ExtendedRange = 3    /**< Mode with one or more extended range transmitters (ERTs) */
   };
   inline std::string getModeString(Mode mode)
   {
      if(Standalone == mode) return "Standalone";
      else if(Standard == mode) return "Standard";
      else if(ExtendedRange == mode) return "Extended Range";
      else return "Unknown mode";
   }

   enum AddressingMode
   {
      NormalAddressing = 0,
      ExpandedAddressing = 1,
      SuperExpandedAddressing = 3,
      UnknownAddressing = 16
   };
   inline std::string getAddressingModeString(AddressingMode addrMode)
   {
      if(NormalAddressing == addrMode) return "Normal Addressing";
      else if(ExpandedAddressing == addrMode) return "Expanded Addressing";
      else if(SuperExpandedAddressing == addrMode) return "Super Expanded Addressing";
      else return "Uknown addressing";
   }

}


/**
 * class for running a Flock of Birds.
 * FlockStandalone is a positional device driver for the Flock of Birds <br>
 *
 * @NOTE: All methods handle errors using the Flock exceptions described above.
 *
 * This driver tries to treat the flock as a single group of birds to read data from.
 * Because of this, most things are done in group mode and through the use of streaming.
 * The driver could be more flexible and allow this to be configured, but it would take a
 * lot more effort and we feel this group mode is the right one to use in most cases.
 */
class FlockStandalone
{
public:
   /**
    * Configure constructor.
    *
    * @param port  such as "/dev/ttyd3"
    * @param baud  such as 38400, 19200, 9600, 14400, etc...
    * @param sync  sync type
    * @param block  blocking
    * @param numBrds  number of birds in flock (without transmitter)
    * @param transmit  transmitter unit number
    * @param hemi  hemisphere to track from
    * @param filt  filtering type
    * @param report  flock report rate
    * @param calfile  a calibration file, if "", then use none
    *
    * @post configures internal data members,
    *          doesn't actually talk to the FOB yet.
    */
   FlockStandalone(std::string port,
                   const int& numBrds = 3,
                   const int& transmit = 3,
                   const int& baud = 38400,
                   const int& sync = 1,
                   const BIRD_HEMI& hemi = LOWER_HEM,
                   const BIRD_FILT& filt = AC_NARROW,
                   Flock::ReportRate = Flock::MaxRate);

   /**  Destructor */
   ~FlockStandalone();

   /** Open the flock on the configured port.
   * This call opens the connection to the flock and
   * asks the flock for its current configuration.
   * Upon completion of this call, the driver should be able to communicate with the flock.
   * @note: We ask the flock for it's configuration here so we can change it later before
   *        calling the configure commands.
   */
   vpr::ReturnStatus openPort(void);

   /** Read the current configuration of the flock.
   * Asks the flock for it's current configuration.
   * This sets internal vars like addressing mode, software rev, etc.
   */
   void readInitialFlockConfiguration();

   /** Configure the flock for execution.
   * @pre Flock is open and all configurable settings have been passed.
   * @post Flock is setup and configured to start getting samples.  It is ready to run.
   */
   vpr::ReturnStatus configure();

   /**
    * Start the flock streaming data.
    * @pre Flock must have been configured and in READY mode.
    */
   vpr::ReturnStatus startStreaming();

   /** Stops the Flock. */
   int stop();

   /**
    * Call this repeatedly to update the data from the birds.
    * @note flock.isActive() must be true to use this function.
    */
   bool sample();

   /** Checks if the flock is active. */
   bool isActive() const;

   /**
    * Sets the port to use.
    * This will be a string in the form of the native OS descriptor.<BR>
    * ex: unix - "/dev/ttyd3", win32 - "COM3"
    */
   void setPort( const std::string& serialPort );

   /**
    * Gets the port used.
    * @see setPort for a description of the string format
    */
   const std::string& getPort() const
   { return mPort; }

   /** Sets the baud rate. */
   void setBaudRate( const int& baud );

   /** Gets the baud rate. */
   const int& getBaudRate() const
   { return mBaud; }

   /**
    * Sets the unit number of the transmitter.
    * @param Transmit An integer that is the same as the dip switch
    *                 setting on the transmitter box (for the unit number).
    *
    * @note flock.isActive() must be false to use this function.
    */
   void setTransmitter( const int& Transmit );

   /**
    * Gets the unit number of the transmitter.
    *
    * @return An integer that is the same as the dip switch
    *         setting on the transmitter box (for the unit number).
    */
   /*inline const int& getTransmitter() const
   {
      return mXmitterUnitNumber;
   }
   */

   /**
    * Sets the number of birds to use in the Flock.
    *
    * @param n An integer number not more than the number of
    *          birds attached to the system.
    * @note flock.isActive() must be false to use this function.
    */
   void setNumBirds( const int& n );

   /**
    * Gets the number of birds to use in the Flock.
    */
   inline const int& getNumBirds() const
   { return mNumBirds; }

   /**
    * Sets the video sync type. Refer to your Flock manual for sync methods and usage.
    */
   void setSync( const vpr::Uint8& sync );

   /**
    * Gets the video sync type.  This option allows the Flock to syncronize its
    * pulses with your video display.  This will eliminate most flicker caused
    * by the magnetic distortion. Refer to your Flock manual for what the
    * returned number means.
    */
   inline vpr::Uint8 getSync() const
   { return mSyncStyle; }

   void setExtendedRange( const bool& blVal );

   /**
    * Sets the type of filtering that the Flock uses.
    * @note flock.isActive() must be false to use this function.
    */
   void setFilterType( const BIRD_FILT& f );

   /** Sets the type of filtering that the Flock uses. */
   inline const BIRD_FILT& getFilterType() const
   { return mFilter; }

   /**
    * Stes the hemisphere that the transmitter transmits from.
    *
    * @note flock.isActive() must be false to use this function.
    */
   void setHemisphere( const BIRD_HEMI& h );

   /** Sets the hemisphere that the transmitter transmits from. */
   inline const BIRD_HEMI& getHemisphere() const
   { return mHemisphere; }

   /**
    * Sets the report rate that the flock uses.
    *
    * @note flock.isActive() must be false to use this function.
    */
   void setReportRate(Flock::ReportRate rRate );

   /** Sets the report rate that the Flock uses. */
   inline Flock::ReportRate getReportRate() const
   { return mReportRate; }

   /** Set the output format to use */
   void setOutputFormat(Flock::Output::Format format);
   Flock::Output::Format getOutputFormat()
   { return mOutputFormat; }

public:
   /** Gets the x position of the i'th reciever. */
   float& xPos( const int& i );

   /** Gets the y position of the i'th reciever. */
   float& yPos( const int& i );

   /** Gets the z position of the i'th reciever. */
   float& zPos( const int& i );

   /** Gets the z rotation of the i'th reciever. */
   float& zRot( const int& i );

   /** Gets the y rotation of the i'th reciever. */
   float& yRot( const int& i );

   /** Gets the x rotation of the i'th reciever. */
   float& xRot( const int& i );

public:
   /** Send command.
   * @param cmd - cmd to send
   */
   void sendCommand(vpr::Uint8 cmd, std::vector<vpr::Uint8> data = std::vector<vpr::Uint8>(0));

   /** Send command to all units (except excluded types)
   */
   void sendCommandAll(vpr::Uint8 cmd, std::vector<vpr::Uint8> data, bool excludeErc=false);

   /**
    * Examines an attribute.
    *
    * @param attrib - Attribute to query for - see the Flock manual.
    * @param respSize - Expected size of the response
    * @param respData   - Returned data
    */
   void getAttribute(vpr::Uint8 attrib, unsigned respSize, std::vector<vpr::Uint8>& respData);

   /**
    * Change an attribute.
    *
    * @param attrib - Attribute to set - see the Flock manual.
    * @param respData - Argument data
    */
   void setAttribute(vpr::Uint8 attrib, std::vector<vpr::Uint8>& attribData);

public:  // ---- Query methods for flock state ---- //
   /** Find the software revision */
   std::pair<unsigned,unsigned> querySoftwareRevision();

   /** Find the model id string */
   std::string queryModelIdString();

   /** Find the addressing mode */
   Flock::AddressingMode queryAddressingMode();

   /** Get the address of the master bird */
   vpr::Uint8 queryAddress();

   /** Get the bird status */
   vpr::Uint16 queryBirdStatus(unsigned addr=0);

   /** Get the system status information */
   std::vector<vpr::Uint8> querySystemStatus();

   // ---- Helpers for printing information of interest to users --- //
   /** Print the information we have about the status of all units in the flock. */
   void printFlockStatus();

   void printError( unsigned char ErrCode, unsigned char ExpandedErrCode );
   int checkError();

   // ---- Attribute getters ------ //
   // These methods are only valid after the initial open command completes
   Flock::AddressingMode getAddressingMode()
   {  return mAddrMode; }
   float getSoftwareRevision()
   {  return mSwRevision; }
   std::string getModelId()
   {  return mModelId; }

protected:     // -- Bird commands --- //
   void pickBird(const vpr::Uint8 birdID);

   // -- Bird commands --- //
   // Documented in impl
   void sendGroupCmd(bool newVal);
   void sendSyncCmd(vpr::Uint8 syncMethod);
   void sendHemisphereCmd(BIRD_HEMI hemi, bool sendToAll);

   void sendAutoconfigCmd(vpr::Uint8 numUnits);
   void sendNextTransmitterCmd(vpr::Uint8 addr, vpr::Uint8 transmitterNumber);
   void sendOutputFormatCmd(Flock::Output::Format format, bool sendToAll);
   //void sendFilter(void);

   void sendReportRateCmd(Flock::ReportRate rate);
   void sendStreamStartCommand();
   void sendStreamStopCommand();


protected: // -- Helpers --- //
   /**
    * Gets a reading.
    *
    * @param n The bird unit number.
    * @param xPos Storage for the x position.
    * @param yPos Storage for the y position.
    * @param zPos Storage for the z position.
    * @param zRot Storage for the rotation about the z-axis.
    * @param yRot Storage for the rotation about the y-axis.
    * @param xRot Storage for the rotation about the x-axis.
    */
   vpr::ReturnStatus getReading(const int& n, float& xPos, float& yPos, float& zPos,
                                float& zRot, float& yRot, float& xRot );

   float rawToFloat(char& r1, char& r2);

   /**
    * Tests if the given bird ID is mapped to the transmitter.
    */
   bool isTransmitter(int birdID) const;

   /** Setup the internal flock units data structure.
   * Reads data from System status and bird status to update the structure
   * @pre Port must be opened and master address must be set.
   */
   void setupFlockUnitsDataStructure();

   /** Get the maximum bird address for the current mode */
   unsigned getMaxBirdAddr();


public:   // --- Enums --- //
   enum Status
   {
      CLOSED,     /**< Flock is closed */
      OPEN,       /**< Flock is open */
      READY,      /**< Configured and ready to run */
      STREAMING   /**< Flock is streaming data */
   };

   // Struct for holding sys information about a single unit in the flock
   struct FlockUnit
   {
      FlockUnit()
         : mAddr(0), mIsMaster(false), mAccessible(false), mIsRunning(false), mHasSensor(false),
           mTransmitterType(Transmitter::None), mHasError(false), mHasBeenInitialized(false)
      {;}

      unsigned mAddr;         /**< Address of this unit on the fbb */
      bool     mIsMaster;
      bool     mAccessible;
      bool     mIsRunning;
      bool     mHasSensor;
      Transmitter::Type mTransmitterType;
      bool     mHasError;
      bool     mHasBeenInitialized;

      bool hasTransmitter() const
      { return (mTransmitterType != Transmitter::None); }
   };


private:  // --- Data members --- //
   FlockStandalone::Status    mStatus;    /**< Current status of the flock */

   std::string       mPort;         /**< Port name to open for serial port connection */
   vpr::SerialPort*  mSerialPort;   /**< Serial port object connected to the bird */
   int               mBaud;         /**< Baud rate to use for connection */

   // --- Configuration information for the flock --- //
   Flock::Mode           mMode;               /**< The mode the flock is operating in */
   Flock::AddressingMode mAddrMode;           /**< The addressing mode of the flock */
   float                 mSwRevision;         /**< Software revision of the flock */
   std::string           mModelId;            /**< Model id for the system we are connected to */
   unsigned              mMasterAddr;         /**< Address of the master */

   int            mNumBirds;           /**< Number of birds in flock */
   int            mXmitterUnitNumber;  /**< Unit number of the transmitter */

   Flock::Output::Format mOutputFormat;   /**< The output format to configure the flock to use */
   Flock::ReportRate     mReportRate;     /**< The report rate we to use when configuring the flock */
   BIRD_HEMI             mHemisphere;     /**< The hemisphere to use when configuring the flock */
   BIRD_FILT             mFilter;         /**< The Filter to use when configuring the flock */
   vpr::Uint8            mSyncStyle;      /**< The sync method to use when configuring the flock */

   typedef std::vector<FlockUnit>   flock_units_t; /**< Type of the flock units sequence */
   flock_units_t           mFlockUnits;              /**< List of all the flock units we have */
   unsigned                mActiveUnitEndIndex;      /**< Index of end of active units (one past last active) */
   std::vector<vpr::Uint8> mXmitterIndices;          /**< Indices into mFlockUnits of the transmitters */

   //    x,y,z,        r,y,p
   float mPosition[MAX_SENSORS][3], mOrientation[MAX_SENSORS][3];

   // --- Default params --- //
   vpr::Interval        mReadTimeout;  /**< Standard timeout for all reads */
};


#endif
