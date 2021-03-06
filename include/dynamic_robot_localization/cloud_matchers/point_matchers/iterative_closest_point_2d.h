#pragma once

/**\file iterative_closest_point_2d.h
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// std includes
#include <limits>
#include <memory>
#include <string>

// PCL includes
#include <pcl/registration/icp.h>
#include <pcl/registration/transformation_estimation_2D.h>

// project includes
#include <dynamic_robot_localization/cloud_matchers/point_matchers/iterative_closest_point.h>
#include <dynamic_robot_localization/convergence_estimators/default_convergence_criteria_with_time.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace dynamic_robot_localization {

// ###############################################################   iterative_closest_point_time_constrained   ################################################################
template <typename PointSource, typename PointTarget, typename Scalar = float>
class IterativeClosestPoint2DTimeConstrained: public pcl::IterativeClosestPoint<PointSource, PointTarget, Scalar> {
	public:
		using Ptr = std::shared_ptr< IterativeClosestPoint2DTimeConstrained<PointSource, PointTarget, Scalar> >;
		using ConstPtr = std::shared_ptr< const IterativeClosestPoint2DTimeConstrained<PointSource, PointTarget, Scalar> >;

		IterativeClosestPoint2DTimeConstrained(double convergence_time_limit_seconds = std::numeric_limits<double>::max()) {
			pcl::IterativeClosestPoint<PointSource, PointTarget, Scalar>::convergence_criteria_.reset(new DefaultConvergenceCriteriaWithTime<Scalar> (
					pcl::Registration<PointSource, PointTarget, Scalar>::nr_iterations_,
					pcl::Registration<PointSource, PointTarget, Scalar>::transformation_,
					*pcl::Registration<PointSource, PointTarget, Scalar>::correspondences_,
					convergence_time_limit_seconds));

			pcl::IterativeClosestPoint<PointSource, PointTarget, Scalar>::transformation_estimation_.reset(new pcl::registration::TransformationEstimation2D<PointSource, PointTarget, Scalar>());
			pcl::Registration<PointSource, PointTarget, Scalar>::reg_name_ = "IterativeClosestPoint2D";
		}

		virtual ~IterativeClosestPoint2DTimeConstrained() {}

		inline double getTransformCloudElapsedTime() { return transform_cloud_elapsed_time_ms_; }
		inline void resetTransformCloudElapsedTime() { transform_cloud_elapsed_time_ms_ = 0; }

	protected:
		virtual void transformCloud(const typename pcl::Registration<PointSource, PointTarget, Scalar>::PointCloudSource &input, typename pcl::Registration<PointSource, PointTarget, Scalar>::PointCloudSource &output, const typename pcl::Registration<PointSource, PointTarget, Scalar>::Matrix4 &transform) {
			PerformanceTimer timer_;
			timer_.start();
			pcl::IterativeClosestPoint<PointSource, PointTarget, Scalar>::transformCloud(input, output, transform);
			transform_cloud_elapsed_time_ms_ += timer_.getElapsedTimeInMilliSec();
		}

		double transform_cloud_elapsed_time_ms_;
};


// ########################################################################   iterative_closest_point   ########################################################################
/**
 * \brief Description...
 */
template <typename PointT>
class IterativeClosestPoint2D : public IterativeClosestPoint<PointT> {
	// ========================================================================   <public-section>   ===========================================================================
	public:
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <usings>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		using Ptr = std::shared_ptr< IterativeClosestPoint2D<PointT> >;
		using ConstPtr = std::shared_ptr< const IterativeClosestPoint2D<PointT> >;
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </usings>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructor>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		IterativeClosestPoint2D() {}
		virtual ~IterativeClosestPoint2D() {}
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructor>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <IterativeClosestPoint-functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		virtual void setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle, ros::NodeHandlePtr& private_node_handle, const std::string& configuration_namespace);
		virtual double getTransformCloudElapsedTimeMS();
		virtual void resetTransformCloudElapsedTime();
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </IterativeClosestPoint-functions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ========================================================================   </public-section>  ===========================================================================

	// ========================================================================   <protected-section>   ========================================================================
	protected:
	// ========================================================================   </protected-section>  ========================================================================
};

} /* namespace dynamic_robot_localization */


#ifdef DRL_NO_PRECOMPILE
#include <dynamic_robot_localization/cloud_matchers/point_matchers/impl/iterative_closest_point_2d.hpp>
#endif

